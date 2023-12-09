#include "../riscv/processor.h"
#include "../abstract_processor/SpikeAbstractProcessor.hpp"
#include "./fake_uncore.hpp"
#include <iostream>
#include <memory>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]){

    const uint64_t program_start = 0x80000000;
    const uint64_t valid_space_len = 0x10000000;
    const uint64_t tohost_addr = 0x80001000;
    const uint64_t fromhost_addr = 0x80001008;
    const uint64_t test_addr = 0x80002000;
    const uint64_t test_init_addr = program_start;

    std::string proj_root = "/work/stu/pguo/code/ArchXplore/ext/riscv-isa-sim";
    // std::string proj_root = getenv("PROJ_ROOT");

    isa_parser_t ip("rv64gcv", "MSU");
    std::vector<mem_cfg_t> mem_cfg { mem_cfg_t(program_start, valid_space_len) };
    std::vector<size_t> hartids = {0};
    cfg_t cfg(std::make_pair(0, 0),
            nullptr,
            "rv64gcv",
            "MSU",
            "vlen:128,elen:64",
            false,
            endianness_little,
            16,
            mem_cfg,
            hartids,
            false,
            4);
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
    // printf("Hello world!\n");    
    int steps = 10000000;

    try{
        std::string testname(argv[1]);
        std::cout << testname << std::endl;
        std::stringstream ss;
        ss << proj_root << "/isatest/";
        ss << testname << ".bin";
        uncore->loadBin(ss.str(), program_start);
        // if(testname.find("-v-") == testname.npos){
        //     std::stringstream ss;
        //     ss << proj_root << "/isatest/";
        //     ss << testname << ".bin";
        //     uncore->loadBin(ss.str(), program_start);
        // }
        // else{
        //     std::stringstream ss;
        //     ss << proj_root << "/isatest/";
        //     ss << testname << ".test.init.bin";
        //     uncore->loadBin(ss.str(), test_init_addr);
        //     ss.str("");
        //     ss << proj_root << "/isatest/";
        //     ss << testname << ".test.bin";
        //     uncore->loadBin(ss.str(), test_addr);
        // }
        // uncore->debugShowMem(program_start);
        processor.reset();
        processor.set_pc(program_start);
        while(1){
            reg_t pc;
            processor.get_pc(pc);
            std::cout << std::hex << pc << ":\t";
            if(pc == 0x80000140) 
                std::cout << "6" << std::endl;
            auto instrPtr = archXplore::SpikeInstr::createInstr(pc);
            processor.fetch(instrPtr);
            std::cout << std::hex << instrPtr->instr_raw << std::endl;
            processor.handleExceptions(instrPtr);
            if(instrPtr->evalid)
                continue;
            processor.execute(instrPtr);
            processor.handleExceptions(instrPtr);
            if(instrPtr->evalid)
                continue;
            processor.writeBack(instrPtr);
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
        return 0;
    }
    uint32_t flag = uncore->peekToHost() >> 1;
    if(steps == 0){
        std::cout << "timeout" << std::endl;
    }
    else if(flag == 0x0)
        std::cout << "test pass" << std::endl;
    else
        std::cout << "test failed @ " << flag << std::endl;
    fclose(outputFile);
    return 0;
}