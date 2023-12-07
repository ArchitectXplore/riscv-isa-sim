#include "../riscv/processor.h"
#include "../abstract_processor/SpikeAbstractProcessor.hpp"
#include "./fake_uncore.hpp"
#include <iostream>
#include <memory>
using namespace std;


int main(){
    isa_parser_t ip("rv64gcv", "MSU");
    std::vector<mem_cfg_t> mem_cfg { mem_cfg_t(0x80000000, 0x10000000) };
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
    std::shared_ptr<archXplore::MemIf::UncoreIf> uncore(new FakeUncore()) ;
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
    
    fclose(outputFile);
    return 0;
}