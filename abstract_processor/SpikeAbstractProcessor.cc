#include "SpikeAbstractProcessor.hpp"
#include <stdio.h>
#include <string.h>
#include <cstring>
namespace archXplore{
std::unordered_map<reg_t, SpikeInstr::PtrType> SpikeInstr::_instrMap 
    = std::unordered_map<reg_t, SpikeInstr::PtrType>();
reg_t SpikeInstr::getXRegVal(const reg_t& reg){
    reg_t ret;
    _processor->getXpr(reg, ret);
    return ret;
}
freg_t SpikeInstr::getFRegVal(const reg_t& reg){
    freg_t ret;
    _processor->getFpr(reg, ret);
    return ret;
}
void SpikeInstr::setXRegVal(const reg_t& reg, const reg_t& val){_processor->setXpr(reg, val);}
void SpikeInstr::setFRegVal(const reg_t& reg, const freg_t& val){_processor->setFpr(reg, val);}



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
void SpikeAbstractProcessor::reset_state() const {
}

void SpikeAbstractProcessor::getPc(reg_t& ret) const {
    ret = _processor->state.pc;
}
void SpikeAbstractProcessor::setPc(const reg_t& pc) {
    _processor->state.pc = pc;
}

void SpikeAbstractProcessor::getXpr(const size_t& idx, reg_t& ret) const {
    ret = _xprf->get(idx);
    // std::cout << "\tget xpr " << idx << ": " << ret << std::endl;
}
void SpikeAbstractProcessor::setXpr(const size_t& idx, const reg_t& val) {
    // std::cout << "\twrite xpr " << idx << ": " << val << std::endl;
    _xprf->write(idx, val);
}

void SpikeAbstractProcessor::getFpr(const size_t& idx, freg_t& ret) const {
    ret = _fprf->get(idx);
    // std::cout << "\tget fpr " << idx << ": " << ret << std::endl;
}
void SpikeAbstractProcessor::setFpr(const size_t& idx, const freg_t& val) {
    _fprf->write(idx, val);
    // std::cout << "\twrite fpr " << idx << ": " << val << std::endl;
}

void SpikeAbstractProcessor::getCsr(const reg_t& idx, reg_t& ret, InstrBase::PtrType instr) const {
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    ret = _processor->get_csr(idx, ptr->instr, false, false);
}
void SpikeAbstractProcessor::peekCsr(const reg_t& idx, reg_t& ret) const noexcept {
    ret = _processor->get_csr(idx, insn_t(0), false, true);
}
void SpikeAbstractProcessor::setCsr(const reg_t& idx, const reg_t& val, InstrBase::PtrType instr) {
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    auto search = _processor->state.csrmap.find(idx);
    if(search == _processor->state.csrmap.end())
        throw "undefined csr idx";
    search->second->verify_permissions(ptr->instr, true);
    search->second->write(val);
}
void SpikeAbstractProcessor::touchCsr(const reg_t& idx, reg_t& val) const noexcept {
    _processor->state.csrmap[idx]->write(val);
}
void SpikeAbstractProcessor::backdoorWriteMIP(const uint64_t& mask, const uint64_t& val){
    _processor->state.mip->backdoor_write_with_mask(mask, val);
}
void SpikeAbstractProcessor::syncTimer(const uint64_t& ticks){
     _processor->state.time->sync(ticks);
}
bool SpikeAbstractProcessor::isWaitingForInterrupt() const noexcept{
    return _processor->in_wfi;
}
void SpikeAbstractProcessor::cleanWaitingForInterrupt() noexcept{
    _processor->in_wfi = false;
}



// * exe if
inline void setException(SpikeInstr::PtrType ptr, trap_t& t){
    ptr->evalid = true;
    ptr->trap = t.clone();
    ptr->ecause = t.cause();
}

void SpikeAbstractProcessor::reset() const{
    _processor->reset();
}
void SpikeAbstractProcessor::run(const bool& trace_enable, const reg_t& n) {
    for (size_t i = 0, steps = 0; i < n; i += steps)
  {
    steps = std::min(n - i, INTERLEAVE - _current_step);
    int count = steps;
    while(count -- > 0 && step(trace_enable)){
    }

    _current_step += steps;
    if (_current_step == INTERLEAVE)
    {
      _current_step = 0;
      _processor->get_mmu()->yield_load_reservation();
    reg_t rtc_ticks = INTERLEAVE / INSNS_PER_RTC_TICK;
    for (auto &dev : _devices) dev->tick(rtc_ticks);
    }
  }
}
bool SpikeAbstractProcessor::step(const bool& trace_enable) {
    // * gen instr
    reg_t pc;
    getPc(pc);
    if(pc == 0x8000018c)
        std::cout << "debug enter" << std::endl;
    if(trace_enable)
        std::cout << std::hex << pc << ":\t";
    auto instrPtr = createInstr(pc);

    // * handle interruption
    handleInterrupts(instrPtr);
    // * wfi 
    if(unlikely(_processor->in_wfi)){
        auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instrPtr);
        SpikeInstr::commitInstr(ptr);
        return false;
    }

    // * fetch 
    // actually this stage contian decode
    if(likely(!instrPtr->evalid)){
        fetch(instrPtr);
        if(trace_enable)
            std::cout << std::hex << instrPtr->getRaw() << std::endl;
    }
    
    // * decode 
    // actually this stage is useless in spike abstract core since fetch can carry out everything
    // still add this stage just for tese
    if(likely(!instrPtr->evalid)){
        decode(instrPtr);
    }

    // * rename
    // this is also a fake rename
    if(likely(!instrPtr->evalid)){
        instrPtr->setAllPrgeAsAreg();
        updateRename(instrPtr);
    }

    // * exe 
    if(likely(!instrPtr->evalid)){
        execute(instrPtr);
    }

    // * commit 
    // actually it just delete the <insn, spikeptr> mapping
    commit(instrPtr);

    // * handle wfi
    if(_processor->in_wfi){
        if(trace_enable)
            std::cout << "  enter wfi" << std::endl;
        return false;
    }

    // * handle exception
    // exception should be handeld after interrupt since interrupt will set up a trap
    if(instrPtr->evalid){
        handleExceptions(instrPtr);
        if(trace_enable)
            std::cout << "  get exception: " << std::hex << instrPtr->ecause << std::endl;
        return !_processor->in_wfi;
    }
    // * get next pc
    advancePc(instrPtr);


    return true;
}


void SpikeAbstractProcessor::fetch(InstrBase::PtrType instr) const{
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    try{
        auto fetch = _processor->mmu->access_icache(ptr->pc)->data;
        ptr->setRaw(fetch.insn.bits());
        ptr->instr = fetch.insn;
        ptr->instr_func = fetch.func;
        return;
    }
    catch(trap_t& t){
        setException(ptr, t);
    }
    catch (wait_for_interrupt_t &t)
    {
        // TODO: have to suspend the running and wait for outside interrupt
      // Return to the outer simulation loop, which gives other devices/harts a
      // chance to generate interrupts.
      //
      // In the debug ROM this prevents us from wasting time looping, but also
      // allows us to switch to other threads only once per idle loop in case
      // there is activity.
      _processor->in_wfi = true;
    }
    return; 
}
void SpikeAbstractProcessor::checkInterrupt(InstrBase::PtrType instr) const{
    if(_processor->state.mip->read() & _processor->state.mie->read())
        instr->ivalid = true;
}
void SpikeAbstractProcessor::decode(InstrBase::PtrType instr) const {
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    try{
        ptr->instr_func = _processor->decode_insn(ptr->getRaw());
        return;
    }
    catch(trap_t& t){
        setException(ptr, t);
    }
    catch (wait_for_interrupt_t &t)
    {
      _processor->in_wfi = true;
    }
    return;
}  
void SpikeAbstractProcessor::updateRename(InstrBase::PtrType instr) const {
    
}  
void SpikeAbstractProcessor::execute(InstrBase::PtrType instr) const {
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    if(instr->pc == 0x800001d8) {
        std::cout << "Debug \n" << std::endl;
    }
    try{
        ptr->npc = ptr->instr_func(_processor.get(), ptr->instr, ptr->pc);
        return;
    }
    catch(trap_t& t){
        setException(ptr, t);
    }
    catch (wait_for_interrupt_t &t)
    {
      _processor->in_wfi = true;
    }
    return; 

}

void SpikeAbstractProcessor::ptw(InstrBase::PtrType instr) const{
    throw "unimpl!";
}
void SpikeAbstractProcessor::handleInterrupts(InstrBase::PtrType instr) const{
    try{
        _processor->take_interrupt(_processor->state.mip->read() & _processor->state.mie->read());
    }
    catch(trap_t& t){
        auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
        setException(ptr, t);
    }
}
void SpikeAbstractProcessor::handleExceptions(InstrBase::PtrType instr) const{
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    if(!ptr->evalid) return;
    //     std::cout << "get exception " << std::hex << ptr->ecause << std::endl;
    _processor->take_trap(*(ptr->trap), ptr->pc);
    auto match = _processor->TM.detect_trap_match(*(ptr->trap));
    if (match.has_value())
        _processor->take_trigger_action(match->action, 0, _processor->state.pc, 0);
    return;
}
void SpikeAbstractProcessor::commit(InstrBase::PtrType instr) const{
    auto ptr = std::dynamic_pointer_cast<SpikeInstr>(instr);
    SpikeInstr::commitInstr(ptr);
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