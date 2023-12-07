#include "../abstract_processor/memif.hpp"
#include <assert.h>
#include <vector>
#include <sstream>
#include <string>
class FakeUncore:public archXplore::MemIf::UncoreIf{
public:
    struct MemChunk{
        std::string name = "default";
        uint64_t paddr;
        uint64_t size;
        char* mem;
        char* getMem(const uint64_t& addr, const uint64_t& s){
            if(addr < paddr || addr+size > paddr + s){
                std::stringstream ss("Bad addr access:");
                ss << "addr " << addr << " ";
                ss << "size " << s << " ";
                ss << "@ memchunk: " << name << " ";
                ss << "paddr " << paddr << " ";
                ss << "size " << size << " ";
                throw ss.str();
            }
            return mem + (addr - paddr);
        }
        bool hit(const uint64_t& addr, const uint64_t& s){
            return (addr < paddr) && (addr + s < paddr + size);
        }
    };
    std::vector<MemChunk> _mem;

    char* getMem(const uint64_t& addr, const uint64_t& s){
        for(auto mem : _mem){
            if(!mem.hit(addr, s)) continue;
            return mem.getMem(addr, s);
        }
        std::stringstream ss("Bad addr access:");
        ss << "addr " << addr << " ";
        ss << "size " << s << " ";
        throw ss.str();
    }
    virtual void sendMemResp(archXplore::MemResp::PtrType resp) override final{
        throw "unimpl!";
    }
    virtual void recieveMemReq(archXplore::MemReq::PtrType req) override final{
        throw "unimpl!";
    }
    virtual void accessMemNoEffect(archXplore::MemReq::PtrType req, archXplore::MemResp::PtrType resp){
        uint64_t addr = req->pa;
        uint64_t size = req->size;
        char* mem = getMem(addr, size);
        resp->data = reinterpret_cast<uint64_t>(mem);
    }
};