#include "../riscv/processor.h"
#include "../abstract_processor/SpikeAbstractProcessor.hpp"
#include "./fake_uncore.hpp"
#include <iostream>
#include <memory>
using namespace std;


int main(){

    const uint64_t program_start = 0xd1010000;
    const uint64_t valid_space_len = 0x10000;
    const uint64_t tohost_addr = 0xd1011000;
    const uint64_t fromhost_addr = 0xd1011008;

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

    try{
        uncore->loadBin("/work/stu/pguo/code/ArchXplore/ext/riscv-isa-sim/isatest/rv64ui-p-addi.bin", program_start);
        // uncore->debugShowMem(program_start);
        processor.reset();
        processor.set_pc(program_start);
        while(1){
            reg_t pc;
            processor.get_pc(pc);
            std::cout << std::hex << pc << std::endl;
            auto instrPtr = archXplore::SpikeInstr::createInstr(pc);
            processor.fetch(instrPtr);
            processor.handleExceptions(instrPtr);
            if(instrPtr->exception->valid)
                continue;
            auto resultPtr = archXplore::SpikeResult::createResult();
            processor.execute(instrPtr, resultPtr);
            processor.handleExceptions(instrPtr);
            if(instrPtr->exception->valid)
                continue;
            processor.advancePc(resultPtr);
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
    if(flag == 0x0)
        std::cout << "test pass" << std::endl;
    else
        std::cout << "test failed @ " << flag << std::endl;
    fclose(outputFile);
    return 0;
}