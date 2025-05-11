#ifndef CONTEXT_H
#define CONTEXT_H
#include <vector>
#include <cstdint>
#include <Memory/Memory.h>

class Context {
    const std::vector<uint8_t> bytes;
    size_t offset;
    Memory::Page_Table pages;
public:
    Context(const std::vector<uint8_t> &bytes, std::string pageFile);
    uint8_t readByte();
    Memory::converted_addr readAddress();
    bool end() const;
};

#endif
