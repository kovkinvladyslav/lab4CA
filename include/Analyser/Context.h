#ifndef CONTEXT_H
#define CONTEXT_H
#include <vector>
#include <cstdint>

class Context {
    const std::vector<uint8_t> bytes;
    size_t offset;
public:
    Context(const std::vector<uint8_t> &bytes);
    uint8_t readByte();
    uint32_t readAddress();
    bool end() const;
};

#endif
