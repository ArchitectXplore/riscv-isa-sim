#include "./SpikeAbstractProcessor.hpp"
#include <stdio.h>
#include <string.h>
#include <cstring>
namespace archXplore{
// * mem if
void SpikeAbstractProcessor::sendMemReq(MemReq::PtrType req) {
    throw "unimpl!";
}
void SpikeAbstractProcessor::recieveMemResp(MemResp::PtrType resp) {
    throw "unimpl!";
}
void SpikeAbstractProcessor::accessMemNoEffect(MemReq::PtrType req, MemResp::PtrType resp) {
}

void SpikeAbstractProcessor::get_clint(const reg_t& idx, reg_t& ret) const {
}
void SpikeAbstractProcessor::set_clint(const reg_t& idx, const reg_t& pc) {
}

// * state if
void SpikeAbstractProcessor::reset() const {
}

void SpikeAbstractProcessor::get_pc(reg_t& ret) const {
    ret = _processor->state.pc;
}
void SpikeAbstractProcessor::set_pc(const reg_t& pc) {
    _processor->state.pc = pc;
}

void SpikeAbstractProcessor::get_xpr(const size_t& idx, reg_t& ret) const {
    ret =  _processor->state.XPR[idx];
}
void SpikeAbstractProcessor::set_xpr(const size_t& idx, const reg_t& val) {
    _processor->state.XPR.write(idx, val);
}

void SpikeAbstractProcessor::get_fpr(const size_t& idx, freg_t& ret) const {
    ret =  _processor->state.FPR[idx];
}
void SpikeAbstractProcessor::set_fpr(const size_t& idx, const freg_t& val) {
    _processor->state.FPR.write(idx, val);
}

void SpikeAbstractProcessor::get_csr(const reg_t& idx, reg_t& ret) const {
    ret = _processor->state.csrmap[idx]->read();
}
void SpikeAbstractProcessor::try_get_csr(const reg_t& idx, reg_t& ret) const noexcept {
    // if(auto it = _processor->state.csrmap.find(idx) != _processor->state.csrmap.end())
    throw "unimpl!";
}
void SpikeAbstractProcessor::set_csr(const reg_t& idx, const reg_t& val) {
    _processor->state.csrmap[idx]->write(val);
}
void SpikeAbstractProcessor::try_set_csr(const reg_t& idx, reg_t& val) const noexcept {
    throw "unimpl!";
}





// * exe if
void setException(SpikeInstr::PtrType ptr, trap_t& t){
    auto excepPtr = std::dynamic_pointer_cast<SpikeException>(ptr->exception);
    excepPtr->valid = true;
    excepPtr->trap = t;
    excepPtr->ecause = t.cause();
}

void SpikeAbstractProcessor::decode(InstrBase::PtrType instr) const {
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    try{
        ptr->instr_func = _processor->decode_insn(ptr->instr_raw);
        return;
    }
    catch(trap_t& t){
        setException(ptr, t);
    }
    return;
}  
void SpikeAbstractProcessor::execute(InstrBase::PtrType instr, ExeResultBase::PtrType exe_result) const {
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    auto result = std::dynamic_pointer_cast<SpikeResult>(exe_result);
    try{
        result->npc = ptr->instr_func(_processor.get(), ptr->instr_raw, ptr->pc);
        return;
    }
    catch(trap_t& t){
        setException(ptr, t);
    }
    return; 

}
void SpikeAbstractProcessor::fetch(InstrBase::PtrType instr) const{
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    try{
        auto fetch = _processor->mmu->access_icache(ptr->pc)->data;
        ptr->instr_func = fetch.func;
        return;
    }
    catch(trap_t& t){
        setException(ptr, t);
    }
    return; 
}
void SpikeAbstractProcessor::ptw(InstrBase::PtrType instr) const{
    throw "unimpl!";
}
void SpikeAbstractProcessor::handleExceptions(InstrBase::PtrType instr) const{
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    auto excepPtr = std::dynamic_pointer_cast<SpikeException>(ptr->exception);
    if(!excepPtr->valid) return;
    _processor->take_trap(excepPtr->trap, ptr->pc);
    auto match = _processor->TM.detect_trap_match(excepPtr->trap);
    if (match.has_value())
        _processor->take_trigger_action(match->action, 0, _processor->state.pc, 0);
    return;
}


// * simif
#define MAX_PADDR_BITS 56 // imposed by Sv39 / Sv48
inline static bool paddr_ok(reg_t addr)
{
  return (addr >> MAX_PADDR_BITS) == 0;
}
char* SpikeAbstractProcessor::addr_to_mem(reg_t paddr){
    if(!paddr_ok(paddr))
        return nullptr;
    // ! size is fixed to 8(64 bit), can be dangerous
    auto mem_req = MemReq::createMemReq(paddr, 0, 8, 0, 0, 0, 0, 0); 
    auto mem_resp = MemResp::createMemResp(0, 0);
    _uncore->accessMemNoEffect(mem_req, mem_resp);
    // uint64 addr to char*
    return  reinterpret_cast<char*>(mem_resp->data);
}
// used for MMIO addresses
bool SpikeAbstractProcessor::mmio_load(reg_t paddr, size_t len, uint8_t* bytes){
    if (paddr + len < paddr || !paddr_ok(paddr + len - 1))
        return false;
    char* mem = addr_to_mem(paddr);
    memcpy(bytes, mem, len);
    return true;
}
bool SpikeAbstractProcessor::mmio_store(reg_t paddr, size_t len, const uint8_t* bytes){
    if (paddr + len < paddr || !paddr_ok(paddr + len - 1))
        return false;
    char* mem = addr_to_mem(paddr);
    memcpy(mem, bytes, len);
    return true;
}
// Callback for processors to let the simulation know they were reset.
void SpikeAbstractProcessor::proc_reset(unsigned id){
    throw "unimpl!";
}

const cfg_t& SpikeAbstractProcessor::get_cfg() const{
    return _processor->get_cfg();
}
const std::map<size_t, processor_t*>& SpikeAbstractProcessor::get_harts() const{
    return _harts;
}

const char* SpikeAbstractProcessor::get_symbol(uint64_t paddr){
    return nullptr;
}   
}