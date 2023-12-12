#include "./util.hpp"
#include <memory>

#include "./memif.hpp"
#include "./InstrBase.hpp"
// #include <stdfloat>

namespace archXplore{
class AbstractProcessorBase: public MemIf::CoreIf{
public:
    using UncorePtr = std::shared_ptr<MemIf::UncoreIf>;
    AbstractProcessorBase(UncorePtr p): _uncore(p){}
    // mem if
    virtual void sendMemReq(MemReq::PtrType) = 0;
    virtual void recieveMemResp(MemResp::PtrType) = 0;
    virtual void accessMemNoEffect(MemReq::PtrType, MemResp::PtrType) = 0;



    // state if
    virtual void reset_state() const = 0;

    virtual void getPc(reg_t& ret) const = 0;
    virtual void setPc(const reg_t& pc) = 0;
    
    virtual void get_xpr(const size_t& idx, reg_t& ret) const = 0;
    virtual void set_xpr(const size_t& idx, const reg_t& val) = 0;

    virtual void get_fpr(const size_t& idx, freg_t& ret) const = 0;
    virtual void set_fpr(const size_t& idx, const freg_t& val) = 0;

    virtual void get_csr(const reg_t& idx, reg_t& ret) const = 0;
    virtual void try_get_csr(const reg_t& idx, reg_t& ret) const noexcept = 0;
    virtual void set_csr(const reg_t& idx, const reg_t& val) = 0;
    virtual void try_set_csr(const reg_t& idx, reg_t& val) const noexcept = 0;

    virtual void backdoorWriteMIP(const uint64_t& mask, const uint64_t& val) = 0;
    virtual void syncTimer(const uint64_t& ticks) = 0;


    // exe if
    virtual void reset() const = 0;
    virtual void checkInterrupt(InstrBase::PtrType instr) const = 0;
    virtual void decode(InstrBase::PtrType instr) const = 0;  
    virtual void updateRename(InstrBase::PtrType instr) const = 0;  
    virtual void execute(InstrBase::PtrType instr) const = 0;
    virtual void fetch(InstrBase::PtrType instr) const = 0;
    virtual void ptw(InstrBase::PtrType instr) const = 0;
    virtual void handleInterrupts(InstrBase::PtrType instr) const = 0;
    virtual void handleExceptions(InstrBase::PtrType instr) const = 0;
    virtual void writeBack(InstrBase::PtrType instr) const = 0;
protected:
    UncorePtr _uncore;
};
}


