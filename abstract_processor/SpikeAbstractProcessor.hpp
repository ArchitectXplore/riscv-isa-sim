#include "AbstractProcessorBase.hpp"
#include "../riscv/simif.h"
#include "../riscv/processor.h"
#include "../riscv/mmu.h"
#include "../riscv/devices.h"
#include <memory>
#include "../riscv/decode_macros.h"
namespace archXplore{
static const size_t INTERLEAVE = 5000;
static const size_t INSNS_PER_RTC_TICK = 100; // 10 MHz clock for 1 BIPS core
class SpikeInstr: public RVInstrBase{
public:
    using PtrType = std::shared_ptr<SpikeInstr>;
    using InstrBase::pc;
    insn_t instr;
    // exception 
    using InstrBase::evalid;
    using InstrBase::ecause;
    using TrapPtr = std::unique_ptr<trap_t>;
    TrapPtr trap;
    // exec result
    using InstrBase::npc;
    insn_func_t instr_func; 
#ifdef ARCHXPLORE_WBSPLIT
    ResultWB resultwb;
#endif // ARCHXPLORE_WBSPLIT

    SpikeInstr(const reg_t& pc){
        this->pc = pc;
    }
    void setAllPrgeAsAreg(){
        _prd = rd();
        _prs1 = rs1();
        _prs2 = rs2();
        _prs3 = rs3();
    }

    static SpikeInstr::PtrType createInstr(const reg_t& pc){
        return std::make_shared<SpikeInstr>(pc);
    }
};
class SpikeAbstractProcessor: public AbstractProcessorBase, public simif_t{
private:
    std::shared_ptr<processor_t> _processor;
    std::map<size_t, processor_t*> _harts;
    using DevicePtr = std::shared_ptr<abstract_device_t>;
    std::vector<DevicePtr> _devices;
    reg_t _current_step = 0;
public:
    using AbstractProcessorBase::UncorePtr;
    SpikeAbstractProcessor(const isa_parser_t *isa, const cfg_t *cfg,
                            uint32_t id, bool halt_on_reset,
                         FILE* log_file, std::ostream& sout_,
                         UncorePtr uncore
                         ):
                         _processor(std::make_shared<processor_t>(isa, cfg, this, id, halt_on_reset, log_file, sout_)),
                         AbstractProcessorBase(uncore)
    {
        _harts[0] = _processor.get();
        debug_mmu = new mmu_t(this, cfg->endianness, nullptr);
        _devices.push_back(std::make_shared<clint_t>(
            this, // simif_t
            0, // freq_hz not important when realtime is false
            false // realtime
        ));
    }
    ~SpikeAbstractProcessor(){
        delete debug_mmu;
    }
    void setSerialized(const bool& flag){_processor->state.serialized = flag;}
    void advancePc(archXplore::SpikeInstr::PtrType ptr){
        if (unlikely(ptr->npc & 1 == 1)) { 
            // std::cout << "problem npc: " << ptr->npc << std::endl;
            switch (ptr->npc) { 
                case 3: _processor->state.serialized = true;break; // PC_SERIALIZE_BEFORE
                case 5: break;  //PC_SERIALIZE_AFTER
                default: abort(); 
            } 
            ptr->npc = _processor->state.pc;
            // break; 
        } else { 
            _processor->state.pc = ptr->npc; 
        }
    }
    void tick(reg_t time){
        for(auto device : _devices)
            device->tick(time);
    }
    bool step(const bool& trace_enable);
    void run(const bool& trace_enable, const reg_t& interval);
    // * from AbstractProcessorBase
    virtual void sendMemReq(MemReq::PtrType)  override final;
    virtual void recieveMemResp(MemResp::PtrType)  override final;
    virtual void accessMemNoEffect(MemReq::PtrType, MemResp::PtrType)  override final;

    virtual void get_clint(const reg_t& idx, reg_t& ret) const  override final;
    virtual void set_clint(const reg_t& idx, const reg_t& val)  override final;


    // state if
    virtual void reset_state() const override final;

    virtual void getPc(reg_t& ret) const override final;
    virtual void setPc(const reg_t& pc) override final;
    
    virtual void get_xpr(const size_t& idx, reg_t& ret) const  override final;
    virtual void set_xpr(const size_t& idx, const reg_t& val)  override final;

    virtual void get_fpr(const size_t& idx, freg_t& ret) const  override final;
    virtual void set_fpr(const size_t& idx, const freg_t& val)  override final;

    virtual void get_csr(const reg_t& idx, reg_t& ret) const  override final;
    virtual void try_get_csr(const reg_t& idx, reg_t& ret) const noexcept  override final;
    virtual void set_csr(const reg_t& idx, const reg_t& val)  override final;
    virtual void try_set_csr(const reg_t& idx, reg_t& val) const noexcept  override final;

    virtual void backdoorWriteMIP(const uint64_t& mask, const uint64_t& val) override final;
    virtual void syncTimer(const uint64_t& ticks) override final;

    // exe if
    virtual void reset() const override final;
    virtual void fetch(InstrBase::PtrType instr) const override final;
    virtual void checkInterrupt(InstrBase::PtrType instr) const override final;  
    virtual void decode(InstrBase::PtrType instr) const override final;  
    virtual void updateRename(InstrBase::PtrType instr) const override final;  
    virtual void execute(InstrBase::PtrType instr) const  override final; 
    virtual void ptw(InstrBase::PtrType instr) const override final;
    virtual void handleInterrupts(InstrBase::PtrType instr) const override final;
    virtual void handleExceptions(InstrBase::PtrType instr) const override final;
    virtual void writeBack(InstrBase::PtrType instr) const override final;

    // simif.h
    virtual char* addr_to_mem(reg_t paddr) override final;
    virtual bool reservable(reg_t paddr) { return addr_to_mem(paddr); }
    // used for MMIO addresses
    virtual bool mmio_fetch(reg_t paddr, size_t len, uint8_t* bytes) { return mmio_load(paddr, len, bytes); }
    virtual bool mmio_load(reg_t paddr, size_t len, uint8_t* bytes) override final;
    virtual bool mmio_store(reg_t paddr, size_t len, const uint8_t* bytes) override final;
    // Callback for processors to let the simulation know they were reset.
    virtual void proc_reset(unsigned id) override final;

    virtual const cfg_t &get_cfg() const override final;
    virtual const std::map<size_t, processor_t*>& get_harts() const override final;

    virtual const char* get_symbol(uint64_t paddr) override final;         
protected:
    using AbstractProcessorBase::_uncore;
};
};