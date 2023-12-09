#include "./util.hpp"
#include <memory>

#include "./memif.hpp"

// #include <stdfloat>

namespace archXplore{

class InstrBase{
public:
    using PtrType = std::shared_ptr<InstrBase>;
    reg_t pc = 0xdeadbeaf;
    reg_t instr_raw = 0xdeadbeaf;
    // exec result
    reg_t npc = 0xdeadbeaf;
    // exception 
    bool evalid = false;
    reg_t ecause = 0xdeadbeaf;
    virtual ~InstrBase() = default;
};   


class AbstractProcessorBase: public MemIf::CoreIf{
public:
    using UncorePtr = std::shared_ptr<MemIf::UncoreIf>;
    AbstractProcessorBase(UncorePtr p): _uncore(p){}
    // mem if
    virtual void sendMemReq(MemReq::PtrType) = 0;
    virtual void recieveMemResp(MemResp::PtrType) = 0;
    virtual void accessMemNoEffect(MemReq::PtrType, MemResp::PtrType) = 0;

    virtual void get_clint(const reg_t& idx, reg_t& ret) const = 0;
    virtual void set_clint(const reg_t& idx, const reg_t& pc) = 0;


    // state if
    virtual void reset_state() const = 0;

    virtual void get_pc(reg_t& ret) const = 0;
    virtual void set_pc(const reg_t& pc) = 0;
    
    virtual void get_xpr(const size_t& idx, reg_t& ret) const = 0;
    virtual void set_xpr(const size_t& idx, const reg_t& val) = 0;

    virtual void get_fpr(const size_t& idx, freg_t& ret) const = 0;
    virtual void set_fpr(const size_t& idx, const freg_t& val) = 0;

    virtual void get_csr(const reg_t& idx, reg_t& ret) const = 0;
    virtual void try_get_csr(const reg_t& idx, reg_t& ret) const noexcept = 0;
    virtual void set_csr(const reg_t& idx, const reg_t& val) = 0;
    virtual void try_set_csr(const reg_t& idx, reg_t& val) const noexcept = 0;



    // exe if
    virtual void reset() const = 0;
    virtual void decode(InstrBase::PtrType instr) const = 0;  
    virtual void execute(InstrBase::PtrType instr) const = 0;
    virtual void fetch(InstrBase::PtrType instr) const = 0;
    virtual void ptw(InstrBase::PtrType instr) const = 0;
    virtual void handleExceptions(InstrBase::PtrType instr) const = 0;
    virtual void writeBack(InstrBase::PtrType instr) const = 0;
protected:
    UncorePtr _uncore;
};
}


