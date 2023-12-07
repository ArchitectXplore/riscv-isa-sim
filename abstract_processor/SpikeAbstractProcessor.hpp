#include "AbstractProcessorBase.hpp"
#include "../riscv/simif.h"
#include "../riscv/processor.h"
#include "../riscv/mmu.h"
#include <memory>
namespace archXplore{
class SpikeException: public ExceptionBase{
public:
    using ExceptionBase::valid;
    using PtrType = std::shared_ptr<SpikeException>;
    reg_t ExceptionBase::ecause;
    trap_t trap;
};

class SpikeInstr: public InstrBase{
public:
    using InstrBase::pc;
    using InstrBase::instr_raw;
    using PtrType = std::shared_ptr<SpikeInstr>;
    insn_func_t instr_func;
};
class SpikeResult: public ExeResultBase{
public:
    using PtrType = std::shared_ptr<SpikeResult>;
    using ExeResultBase::npc;
    using ExeResultBase::result_val;
};
class SpikeAbstractProcessor: public AbstractProcessorBase, public simif_t{
private:
    std::shared_ptr<processor_t> _processor;
    std::map<size_t, processor_t*> _harts;

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
    }
    ~SpikeAbstractProcessor(){
    }
    virtual void sendMemReq(MemReq::PtrType)  override final;
    virtual void recieveMemResp(MemResp::PtrType)  override final;
    virtual void accessMemNoEffect(MemReq::PtrType, MemResp::PtrType)  override final;

    virtual void get_clint(const reg_t& idx, reg_t& ret) const  override final;
    virtual void set_clint(const reg_t& idx, const reg_t& val)  override final;


    // state if
    virtual void reset() const  override final;

    virtual void get_pc(reg_t& ret) const override final;
    virtual void set_pc(const reg_t& pc) override final;
    
    virtual void get_xpr(const size_t& idx, reg_t& ret) const  override final;
    virtual void set_xpr(const size_t& idx, const reg_t& val)  override final;

    virtual void get_fpr(const size_t& idx, freg_t& ret) const  override final;
    virtual void set_fpr(const size_t& idx, const freg_t& val)  override final;

    virtual void get_csr(const reg_t& idx, reg_t& ret) const  override final;
    virtual void try_get_csr(const reg_t& idx, reg_t& ret) const noexcept  override final;
    virtual void set_csr(const reg_t& idx, const reg_t& val)  override final;
    virtual void try_set_csr(const reg_t& idx, reg_t& val) const noexcept  override final;





    // exe if
    virtual void decode(InstrBase::PtrType instr) const  override final;  
    virtual void execute(InstrBase::PtrType instr, ExeResultBase::PtrType exe_result) const  override final; 
    virtual void fetch(InstrBase::PtrType instr) const override final;
    virtual void ptw(InstrBase::PtrType instr) const override final;
    virtual void handleExceptions(InstrBase::PtrType instr) const override final;

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