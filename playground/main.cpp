#include "../riscv/processor.h"
#include "../abstract_processor/SpikeAbstractProcessor.hpp"
#include "./fake_uncore.hpp"
#include <iostream>
#include <memory>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]){
    // TODO: rv64ud-p-move: tohost is 0x80002000
    const uint64_t program_start = 0x80000000;
    const uint64_t valid_space_len = 0x10000000;
    const uint64_t tohost_addr = 0x80001000;
    const uint64_t fromhost_addr = 0x80001008;
    const uint64_t test_addr = 0x80002000;
    const uint64_t test_init_addr = program_start;
    int return_flag = 0;

    std::string proj_root = "/work/stu/pguo/code/ArchXplore/ext/riscv-isa-sim";
    // std::string proj_root = getenv("PROJ_ROOT");

    std::vector<mem_cfg_t> mem_cfg { mem_cfg_t(program_start, valid_space_len) };
    std::vector<size_t> hartids = {0};
    cfg_t cfg(/*default_initrd_bounds=*/std::make_pair((reg_t)0, (reg_t)0),
            /*default_bootargs=*/nullptr,
            /*default_isa=*/DEFAULT_ISA,
            /*default_priv=*/DEFAULT_PRIV,
            /*default_varch=*/DEFAULT_VARCH,
            /*default_misaligned=*/false,
            /*default_endianness*/endianness_little,
            /*default_pmpregions=*/16,
            /*default_mem_layout=*/mem_cfg,
            /*default_hartids=*/std::vector<size_t>(),
            /*default_real_time_clint=*/false,
            /*default_trigger_count=*/4);
    isa_parser_t ip(cfg.isa(), cfg.priv());
    FILE* outputFile = fopen("./log.txt", "w");
    std::shared_ptr<FakeUncore> uncore = std::make_shared<FakeUncore>(mem_cfg, tohost_addr);
    archXplore::SpikeAbstractProcessor processor(
        &ip,
        &cfg,
        0,
        false,
        outputFile,
        cout,
        uncore
    );
    bool trace_enable = false;
    int steps = 100000;
    try{
        std::string testname(argv[1]);
        std::cout << testname << ": ";
        std::stringstream ss;
        ss << proj_root << "/isatest/";
        ss << testname << ".bin";
        if (argc > 2){
            std::string argv_2 = argv[2];
            if(argv_2 == "--trace"){
                trace_enable = true;
            }
        }
        
        uncore->loadBin(ss.str(), program_start);
        processor.reset();
        processor.setPc(program_start);
        while(steps > 0){
            steps --;
            // * gen instr
            reg_t pc;
            processor.getPc(pc);
            if(trace_enable)
                std::cout << std::hex << pc << ":\t";
            auto instrPtr = archXplore::SpikeInstr::createInstr(pc);

            // * fetch 
            // actually this stage contian decode
            if(likely(!instrPtr->evalid)){
                processor.fetch(instrPtr);
                if(trace_enable)
                    std::cout << std::hex << instrPtr->getRaw() << std::endl;
                processor.checkInterrupt(instrPtr);
            }
            
            // * decode 
            // actually this stage is useless in spike abstract core since fetch can carry out everything
            // still add this stage just for tese
            if(likely(!instrPtr->evalid)){
                processor.decode(instrPtr);
                processor.checkInterrupt(instrPtr);
            }

            // * rename
            // this is also a fake rename
            instrPtr->setAllPrgeAsAreg();
            processor.updateRename(instrPtr);

            // * exe 
            if(likely(!instrPtr->evalid)){
                processor.execute(instrPtr);
                processor.checkInterrupt(instrPtr);
            }

            // * handle interruption
            if(instrPtr->ivalid){
                processor.handleInterrupts(instrPtr);
                if(trace_enable)
                    std::cout << "  get a interrupt or a interrupt is pending" << std::endl;
            }

            // * handle exception
            // exception should be handeld after interrupt since interrupt will set up a trap
            if(instrPtr->evalid){
                processor.handleExceptions(instrPtr);
                if(trace_enable)
                    std::cout << "  get exception: " << std::hex << instrPtr->ecause << std::endl;
                continue;
            }
            

            // * wb
            // this is only abled when macro ARCHXPLORE_WBSPLIT is defined
            processor.writeBack(instrPtr);

            // * get next pc
            processor.advancePc(instrPtr);
            if(uncore->peekToHost() & 0x1 == 0x1)
                break;
        }

        // printf("%d\n", uncore->getbyte(tohost_addr));
        // uncore->setbyte(tohost_addr, 1);
        // printf("%d\n", uncore->getbyte(tohost_addr));
        // printf("%d\n", uncore->peekToHost());
    }
    catch(const std::string& s){
        std::cout << "test failed. Get Exception:\n";
        std::cout << s << std::endl;
    }

    uint32_t flag = uncore->peekToHost() >> 1;
    if(steps == 0){
        std::cout << "test timeout" << std::endl;
        return_flag = 2;
    }
    else if(flag == 0x0){
        std::cout << "test pass" << std::endl;
        return_flag = 1;
    }
    else{
        std::cout << "test failed @ " << flag << std::endl;
        return_flag = 3;
    }
    fclose(outputFile);
    return return_flag;
}