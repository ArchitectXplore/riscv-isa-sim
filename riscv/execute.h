/* Automatically generated by parse-opcodes */
switch((insn.bits >> 0x19) & 0x7f)
{
  case 0x0:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xffffffff) == 0x0)
        {
          #include "insns/unimp.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x60:
  {
    #include "insns/j.h"
    break;
  }
  case 0x61:
  {
    #include "insns/jal.h"
    break;
  }
  case 0x68:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x2:
      {
        #include "insns/l_s.h"
        break;
      }
      case 0x3:
      {
        #include "insns/l_d.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x69:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x2:
      {
        #include "insns/s_s.h"
        break;
      }
      case 0x3:
      {
        #include "insns/s_d.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x6a:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xffff8000) == 0xd40a8000)
        {
          #include "insns/c_eq_s.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4028000)
        {
          #include "insns/sgninj_s.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd4070000)
        {
          #include "insns/cvt_s_w.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4000000)
        {
          #include "insns/add_s.h"
          break;
        }
        if((insn.bits & 0xffff83e0) == 0xd42c0000)
        {
          #include "insns/mff_s.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd42e0000)
        {
          #include "insns/mtf_s.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4030000)
        {
          #include "insns/sgninjn_s.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd4078000)
        {
          #include "insns/cvtu_s_w.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd4068000)
        {
          #include "insns/cvtu_s_l.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd4060000)
        {
          #include "insns/cvt_s_l.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4008000)
        {
          #include "insns/sub_s.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd4020000)
        {
          #include "insns/sqrt_s.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd40b0000)
        {
          #include "insns/c_lt_s.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4038000)
        {
          #include "insns/sgnmul_s.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4018000)
        {
          #include "insns/div_s.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd4098000)
        {
          #include "insns/cvt_s_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd40b8000)
        {
          #include "insns/c_le_s.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd4010000)
        {
          #include "insns/mul_s.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        if((insn.bits & 0xffcffc00) == 0xd4478000)
        {
          #include "insns/cvtu_s_w_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4440000)
        {
          #include "insns/cvt_l_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4468000)
        {
          #include "insns/cvtu_s_l_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd4410000)
        {
          #include "insns/mul_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4448000)
        {
          #include "insns/cvtu_l_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4470000)
        {
          #include "insns/cvt_s_w_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4420000)
        {
          #include "insns/sqrt_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4498000)
        {
          #include "insns/cvt_s_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd4408000)
        {
          #include "insns/sub_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd4418000)
        {
          #include "insns/div_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4460000)
        {
          #include "insns/cvt_s_l_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd4400000)
        {
          #include "insns/add_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4450000)
        {
          #include "insns/cvt_w_s_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd4458000)
        {
          #include "insns/cvtu_w_s_rm.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x6:
      {
        if((insn.bits & 0xffff83e0) == 0xd5ac0000)
        {
          #include "insns/mff_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5828000)
        {
          #include "insns/sgninj_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5818000)
        {
          #include "insns/div_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd58a8000)
        {
          #include "insns/c_eq_d.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5868000)
        {
          #include "insns/cvtu_d_l.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5878000)
        {
          #include "insns/cvtu_d_w.h"
          break;
        }
        if((insn.bits & 0xffff83e0) == 0xd5ac8000)
        {
          #include "insns/mffl_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5838000)
        {
          #include "insns/sgnmul_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5800000)
        {
          #include "insns/add_d.h"
          break;
        }
        if((insn.bits & 0xffff83e0) == 0xd5ad0000)
        {
          #include "insns/mffh_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd58b8000)
        {
          #include "insns/c_le_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5830000)
        {
          #include "insns/sgninjn_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5be0000)
        {
          #include "insns/mtflh_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5808000)
        {
          #include "insns/sub_d.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5ae0000)
        {
          #include "insns/mtf_d.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5820000)
        {
          #include "insns/sqrt_d.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5880000)
        {
          #include "insns/cvt_d_s.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5870000)
        {
          #include "insns/cvt_d_w.h"
          break;
        }
        if((insn.bits & 0xfffffc00) == 0xd5860000)
        {
          #include "insns/cvt_d_l.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd5810000)
        {
          #include "insns/mul_d.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xd58b0000)
        {
          #include "insns/c_lt_d.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        if((insn.bits & 0xffcffc00) == 0xd5c60000)
        {
          #include "insns/cvt_d_l_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd5c50000)
        {
          #include "insns/cvt_w_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd5c58000)
        {
          #include "insns/cvtu_w_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd5c20000)
        {
          #include "insns/sqrt_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd5c68000)
        {
          #include "insns/cvtu_d_l_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd5c00000)
        {
          #include "insns/add_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd5c40000)
        {
          #include "insns/cvt_l_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcffc00) == 0xd5c48000)
        {
          #include "insns/cvtu_l_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd5c10000)
        {
          #include "insns/mul_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd5c18000)
        {
          #include "insns/div_d_rm.h"
          break;
        }
        if((insn.bits & 0xffcf8000) == 0xd5c08000)
        {
          #include "insns/sub_d_rm.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x6b:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xffffffe0) == 0xd6008000)
        {
          #include "insns/di.h"
          break;
        }
        if((insn.bits & 0xffffffe0) == 0xd6000000)
        {
          #include "insns/ei.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        if((insn.bits & 0xffff83e0) == 0xd6400000)
        {
          #include "insns/mfpcr.h"
          break;
        }
        if((insn.bits & 0xffff801f) == 0xd6408000)
        {
          #include "insns/mtpcr.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x2:
      {
        if((insn.bits & 0xffffffff) == 0xd6800000)
        {
          #include "insns/eret.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x6c:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xfff00000) == 0xd8000000)
        {
          #include "insns/madd_s.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        #include "insns/madd_s_rm.h"
        break;
      }
      case 0x6:
      {
        if((insn.bits & 0xfff00000) == 0xd9800000)
        {
          #include "insns/madd_d.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        #include "insns/madd_d_rm.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x6d:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xfff00000) == 0xda000000)
        {
          #include "insns/msub_s.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        #include "insns/msub_s_rm.h"
        break;
      }
      case 0x6:
      {
        if((insn.bits & 0xfff00000) == 0xdb800000)
        {
          #include "insns/msub_d.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        #include "insns/msub_d_rm.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x6e:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xfff00000) == 0xdc000000)
        {
          #include "insns/nmsub_s.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        #include "insns/nmsub_s_rm.h"
        break;
      }
      case 0x6:
      {
        if((insn.bits & 0xfff00000) == 0xdd800000)
        {
          #include "insns/nmsub_d.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        #include "insns/nmsub_d_rm.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x6f:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xfff00000) == 0xde000000)
        {
          #include "insns/nmadd_s.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        #include "insns/nmadd_s_rm.h"
        break;
      }
      case 0x6:
      {
        if((insn.bits & 0xfff00000) == 0xdf800000)
        {
          #include "insns/nmadd_d.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        #include "insns/nmadd_d_rm.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x71:
  {
    #include "insns/lui.h"
    break;
  }
  case 0x72:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        #include "insns/jalr_c.h"
        break;
      }
      case 0x1:
      {
        #include "insns/jalr_r.h"
        break;
      }
      case 0x2:
      {
        #include "insns/jalr_j.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x73:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        #include "insns/beq.h"
        break;
      }
      case 0x1:
      {
        #include "insns/bne.h"
        break;
      }
      case 0x4:
      {
        #include "insns/blt.h"
        break;
      }
      case 0x5:
      {
        #include "insns/bge.h"
        break;
      }
      case 0x6:
      {
        #include "insns/bltu.h"
        break;
      }
      case 0x7:
      {
        #include "insns/bgeu.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x74:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        #include "insns/addi.h"
        break;
      }
      case 0x2:
      {
        #include "insns/slti.h"
        break;
      }
      case 0x3:
      {
        #include "insns/sltiu.h"
        break;
      }
      case 0x4:
      {
        #include "insns/andi.h"
        break;
      }
      case 0x5:
      {
        #include "insns/ori.h"
        break;
      }
      case 0x6:
      {
        #include "insns/xori.h"
        break;
      }
      case 0x7:
      {
        if((insn.bits & 0xffff0000) == 0xe9c20000)
        {
          #include "insns/srli.h"
          break;
        }
        if((insn.bits & 0xffff0000) == 0xe9c30000)
        {
          #include "insns/srai.h"
          break;
        }
        if((insn.bits & 0xffff0000) == 0xe9c10000)
        {
          #include "insns/slli.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x75:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xffff8000) == 0xea000000)
        {
          #include "insns/add.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea038000)
        {
          #include "insns/nor.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea018000)
        {
          #include "insns/sltu.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea030000)
        {
          #include "insns/xor.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea008000)
        {
          #include "insns/sub.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea028000)
        {
          #include "insns/or.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea010000)
        {
          #include "insns/slt.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea020000)
        {
          #include "insns/and.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        if((insn.bits & 0xffff8000) == 0xea400000)
        {
          #include "insns/mul.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea420000)
        {
          #include "insns/div.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea430000)
        {
          #include "insns/rem.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea410000)
        {
          #include "insns/mulh.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea438000)
        {
          #include "insns/remu.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea418000)
        {
          #include "insns/mulhu.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xea428000)
        {
          #include "insns/divu.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        if((insn.bits & 0xffff8000) == 0xebc30000)
        {
          #include "insns/sra.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xebc20000)
        {
          #include "insns/srl.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xebc10000)
        {
          #include "insns/sll.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x76:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        #include "insns/addiw.h"
        break;
      }
      case 0x7:
      {
        if((insn.bits & 0xffff8000) == 0xedc10000)
        {
          #include "insns/slliw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xedc20000)
        {
          #include "insns/srliw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xedc30000)
        {
          #include "insns/sraiw.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x77:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xffff8000) == 0xee000000)
        {
          #include "insns/addw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee008000)
        {
          #include "insns/subw.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        if((insn.bits & 0xffff8000) == 0xee438000)
        {
          #include "insns/remuw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee428000)
        {
          #include "insns/divuw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee418000)
        {
          #include "insns/mulhuw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee400000)
        {
          #include "insns/mulw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee430000)
        {
          #include "insns/remw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee410000)
        {
          #include "insns/mulhw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xee420000)
        {
          #include "insns/divw.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x7:
      {
        if((insn.bits & 0xffff8000) == 0xefc20000)
        {
          #include "insns/srlw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xefc30000)
        {
          #include "insns/sraw.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xefc10000)
        {
          #include "insns/sllw.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x78:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        #include "insns/lb.h"
        break;
      }
      case 0x1:
      {
        #include "insns/lh.h"
        break;
      }
      case 0x2:
      {
        #include "insns/lw.h"
        break;
      }
      case 0x3:
      {
        #include "insns/ld.h"
        break;
      }
      case 0x4:
      {
        #include "insns/lbu.h"
        break;
      }
      case 0x5:
      {
        #include "insns/lhu.h"
        break;
      }
      case 0x6:
      {
        #include "insns/lwu.h"
        break;
      }
      case 0x7:
      {
        if((insn.bits & 0xffc0001f) == 0xf1c00000)
        {
          #include "insns/synci.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x79:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        #include "insns/sb.h"
        break;
      }
      case 0x1:
      {
        #include "insns/sh.h"
        break;
      }
      case 0x2:
      {
        #include "insns/sw.h"
        break;
      }
      case 0x3:
      {
        #include "insns/sd.h"
        break;
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x7a:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x2:
      {
        if((insn.bits & 0xffff8000) == 0xf4828000)
        {
          #include "insns/amow_max.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4810000)
        {
          #include "insns/amow_and.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4820000)
        {
          #include "insns/amow_min.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4818000)
        {
          #include "insns/amow_or.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4830000)
        {
          #include "insns/amow_minu.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4800000)
        {
          #include "insns/amow_add.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4808000)
        {
          #include "insns/amow_swap.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4838000)
        {
          #include "insns/amow_maxu.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x3:
      {
        if((insn.bits & 0xffff8000) == 0xf4c00000)
        {
          #include "insns/amo_add.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c08000)
        {
          #include "insns/amo_swap.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c18000)
        {
          #include "insns/amo_or.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c28000)
        {
          #include "insns/amo_max.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c20000)
        {
          #include "insns/amo_min.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c30000)
        {
          #include "insns/amo_minu.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c10000)
        {
          #include "insns/amo_and.h"
          break;
        }
        if((insn.bits & 0xffff8000) == 0xf4c38000)
        {
          #include "insns/amo_maxu.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  case 0x7b:
  {
    switch((insn.bits >> 0x16) & 0x7)
    {
      case 0x0:
      {
        if((insn.bits & 0xffffffe0) == 0xf6000000)
        {
          #include "insns/rdnpc.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x1:
      {
        if((insn.bits & 0xffff83e0) == 0xf6400000)
        {
          #include "insns/mfcr.h"
          break;
        }
        if((insn.bits & 0xffff801f) == 0xf6408000)
        {
          #include "insns/mtcr.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x2:
      {
        if((insn.bits & 0xffffffff) == 0xf6800000)
        {
          #include "insns/sync.h"
          break;
        }
        #include "insns/unimp.h"
      }
      case 0x3:
      {
        if((insn.bits & 0xffc003ff) == 0xf6c00000)
        {
          #include "insns/syscall.h"
          break;
        }
        #include "insns/unimp.h"
      }
      default:
      {
        #include "insns/unimp.h"
      }
    }
    break;
  }
  default:
  {
    #include "insns/unimp.h"
  }
}
