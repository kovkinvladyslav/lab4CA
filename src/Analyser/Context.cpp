#include <Analyser/Context.h>

Context::Context(const std::vector<uint8_t> &bytes) : bytes(bytes), offset(0)
{}

uint8_t Context::readByte(){
    return bytes[offset++];
}

uint32_t Context::readAddress(){
    uint32_t val = 0;
    for (int i = 0; i < 4; ++i){
        val = (val << 8) | readByte();
    }

    return val;
}

bool Context::end() const {
    return offset >= bytes.size();
}
