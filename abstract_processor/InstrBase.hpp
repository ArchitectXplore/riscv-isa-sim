#ifndef __INSTR_BASE_HPP__
#define __INSTR_BASE_HPP__
#include "./util.hpp"
#include <memory>
namespace archXplore{
class InstrBase{
public:
    using PtrType = std::shared_ptr<InstrBase>;
    reg_t pc = 0xdeadbeaf;
    // exec result
    reg_t npc = 0xdeadbeaf;
    // exception 
    bool evalid = false;
    reg_t ecause = 0xdeadbeaf;
    //interrupt
    bool ivalid = false;

    reg_t getRaw() const {return _raw;}
    void setRaw(const reg_t& raw){_raw = raw;}

    
    uint64_t prd() { return _prd; }
    uint64_t prs1() { return _prs1; }
    uint64_t prs2() { return _prs2; }
    uint64_t prs3() { return _prs3; }
    void set_prd(const uint64_t& prd)   {_prd = prd; }
    void set_prs1(const uint64_t& prs1) {_prs1 = prs1; }
    void set_prs2(const uint64_t& prs2) {_prs2 = prs2; }
    void set_prs3(const uint64_t& prs3) {_prs3 = prs3; }
    virtual ~InstrBase() = default;
protected:
    reg_t _raw = 0xdeadbeaf;
    reg_t _prs1;
    reg_t _prs2;
    reg_t _prs3;
    reg_t _prd;
    reg_t _getBits(const int& lo, const int& len) { return (_raw >> lo) & ((reg_t(1) << len) - 1); }
    reg_t _getBitsSigned(int lo, int len) { return int64_t(_raw) << (64 - lo - len) >> (64 - len); }
}; 

class RVInstrBase: public InstrBase{
public:
    const reg_t XREG_RA = 1;
    const reg_t XREG_SP = 2;
    const reg_t XREG_S0 = 8;
    const reg_t XREG_A0 = 10;
    const reg_t XREG_A1 = 11;
    const reg_t XREG_Sn = 16;
    using PtrType = std::shared_ptr<RVInstrBase>;
    
    virtual ~RVInstrBase() = default;

    // TODO: unfinished. There may be more cases
    // ! need to return the REAL reg in the case of rvc
    uint64_t ger_rd() {
        return rd();
    }
    uint64_t ger_rs1() {
        return rs1();
    }
    uint64_t ger_rs2() {
        return rs2();
    }
    uint64_t ger_rs3() {
        return rs3();
    }

    int length() { return _insn_length(_raw); }
    bool isC(){return length() == 2;}
    int64_t i_imm() { return _getBitsSigned(20, 12); }
    int64_t shamt() { return _getBits(20, 6); }
    int64_t s_imm() { return _getBits(7, 5) + (_getBitsSigned(25, 7) << 5); }
    int64_t sb_imm() { return (_getBits(8, 4) << 1) + (_getBits(25, 6) << 5) + (_getBits(7, 1) << 11) + (imm_sign() << 12); }
    int64_t u_imm() { return _getBitsSigned(12, 20) << 12; }
    int64_t uj_imm() { return (_getBits(21, 10) << 1) + (_getBits(20, 1) << 11) + (_getBits(12, 8) << 12) + (imm_sign() << 20); }
    uint64_t rd() { return _getBits(7, 5); }
    uint64_t rs1() { return _getBits(15, 5); }
    uint64_t rs2() { return _getBits(20, 5); }
    uint64_t rs3() { return _getBits(27, 5); }
    uint64_t rm() { return _getBits(12, 3); }
    uint64_t csr() { return _getBits(20, 12); }
    uint64_t iorw() { return _getBits(20, 8); }
    uint64_t bs() { return _getBits(30, 2); } // Crypto ISE - SM4/AES32 byte select.
    uint64_t rcon() { return _getBits(20, 4); } // Crypto ISE - AES64 round const.

    int64_t rvc_imm() { return _getBits(2, 5) + (_getBitsSigned(12, 1) << 5); }
    int64_t rvc_zimm() { return _getBits(2, 5) + (_getBits(12, 1) << 5); }
    int64_t rvc_addi4spn_imm() { return (_getBits(6, 1) << 2) + (_getBits(5, 1) << 3) + (_getBits(11, 2) << 4) + (_getBits(7, 4) << 6); }
    int64_t rvc_addi16sp_imm() { return (_getBits(6, 1) << 4) + (_getBits(2, 1) << 5) + (_getBits(5, 1) << 6) + (_getBits(3, 2) << 7) + (_getBitsSigned(12, 1) << 9); }
    int64_t rvc_lwsp_imm() { return (_getBits(4, 3) << 2) + (_getBits(12, 1) << 5) + (_getBits(2, 2) << 6); }
    int64_t rvc_ldsp_imm() { return (_getBits(5, 2) << 3) + (_getBits(12, 1) << 5) + (_getBits(2, 3) << 6); }
    int64_t rvc_swsp_imm() { return (_getBits(9, 4) << 2) + (_getBits(7, 2) << 6); }
    int64_t rvc_sdsp_imm() { return (_getBits(10, 3) << 3) + (_getBits(7, 3) << 6); }
    int64_t rvc_lw_imm() { return (_getBits(6, 1) << 2) + (_getBits(10, 3) << 3) + (_getBits(5, 1) << 6); }
    int64_t rvc_ld_imm() { return (_getBits(10, 3) << 3) + (_getBits(5, 2) << 6); }
    int64_t rvc_j_imm() { return (_getBits(3, 3) << 1) + (_getBits(11, 1) << 4) + (_getBits(2, 1) << 5) + (_getBits(7, 1) << 6) + (_getBits(6, 1) << 7) + (_getBits(9, 2) << 8) + (_getBits(8, 1) << 10) + (_getBitsSigned(12, 1) << 11); }
    int64_t rvc_b_imm() { return (_getBits(3, 2) << 1) + (_getBits(10, 2) << 3) + (_getBits(2, 1) << 5) + (_getBits(5, 2) << 6) + (_getBitsSigned(12, 1) << 8); }
    int64_t rvc_simm3() { return _getBits(10, 3); }
    uint64_t rvc_rd() { return rd(); }
    uint64_t rvc_rs1() { return rd(); }
    uint64_t rvc_rs2() { return _getBits(2, 5); }
    uint64_t rvc_rs1s() { return 8 + _getBits(7, 3); }
    uint64_t rvc_rs2s() { return 8 + _getBits(2, 3); }

    uint64_t rvc_lbimm() { return (_getBits(5, 1) << 1) + _getBits(6, 1); }
    uint64_t rvc_lhimm() { return (_getBits(5, 1) << 1); }

    uint64_t rvc_r1sc() { return _getBits(7, 3); }
    uint64_t rvc_r2sc() { return _getBits(2, 3); }
    uint64_t rvc_rlist() { return _getBits(4, 4); }
    uint64_t rvc_spimm() { return _getBits(2, 2) << 4; }

    uint64_t rvc_index() { return _getBits(2, 8); }

    uint64_t v_vm() { return _getBits(25, 1); }
    uint64_t v_wd() { return _getBits(26, 1); }
    uint64_t v_nf() { return _getBits(29, 3); }
    uint64_t v_simm5() { return _getBitsSigned(15, 5); }
    uint64_t v_zimm5() { return _getBits(15, 5); }
    uint64_t v_zimm10() { return _getBits(20, 10); }
    uint64_t v_zimm11() { return _getBits(20, 11); }
    uint64_t v_lmul() { return _getBits(20, 2); }
    uint64_t v_frac_lmul() { return _getBits(22, 1); }
    uint64_t v_sew() { return 1 << (_getBits(23, 3) + 3); }
    uint64_t v_width() { return _getBits(12, 3); }
    uint64_t v_mop() { return _getBits(26, 2); }
    uint64_t v_lumop() { return _getBits(20, 5); }
    uint64_t v_sumop() { return _getBits(20, 5); }
    uint64_t v_vta() { return _getBits(26, 1); }
    uint64_t v_vma() { return _getBits(27, 1); }
    uint64_t v_mew() { return _getBits(28, 1); }
    uint64_t v_zimm6() { return _getBits(15, 5) + (_getBits(26, 1) << 5); }

    uint64_t p_imm2() { return _getBits(20, 2); }
    uint64_t p_imm3() { return _getBits(20, 3); }
    uint64_t p_imm4() { return _getBits(20, 4); }
    uint64_t p_imm5() { return _getBits(20, 5); }
    uint64_t p_imm6() { return _getBits(20, 6); }

    uint64_t zcmp_regmask() {
        unsigned mask = 0;
        uint64_t rlist = rvc_rlist();

        if (rlist >= 4)
        mask |= 1U << XREG_RA;

        for (reg_t i = 5; i <= rlist; i++)
            mask |= 1U << _sn(i - 5);

        if (rlist == 15)
        mask |= 1U << _sn(11);

        return mask;
    }

    uint64_t zcmp_stack_adjustment(int xlen) {
        reg_t stack_adj_base = 0;
        switch (rvc_rlist()) {
        case 15:
        stack_adj_base += 16;
        case 14:
        if (xlen == 64)
            stack_adj_base += 16;
        case 13:
        case 12:
        stack_adj_base += 16;
        case 11:
        case 10:
        if (xlen == 64)
            stack_adj_base += 16;
        case 9:
        case 8:
        stack_adj_base += 16;
        case 7:
        case 6:
        if (xlen == 64)
            stack_adj_base += 16;
        case 5:
        case 4:
        stack_adj_base += 16;
        break;
        }

        return stack_adj_base + rvc_spimm();
    }
    uint64_t imm_sign() { return _getBitsSigned(31, 1); }
private:
    inline int _insn_length(const reg_t& x){
        return 
            (((x) & 0x03) < 0x03 ? 2 : 
            ((x) & 0x1f) < 0x1f ? 4 : 
            ((x) & 0x3f) < 0x3f ? 6 : 
            8);
    } 
    inline reg_t _sn(const reg_t& n) {
        return (n) < 2 ? XREG_S0 + (n) : XREG_Sn + (n);
    }

};  
}
#endif //__INSTR_BASE_HPP__