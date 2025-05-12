#include <Analyser/Context.h>

Context::Context(const std::vector<uint8_t> &bytes, std::string pageFile) : bytes(bytes), offset(0), pages(pageFile)
{}

uint8_t Context::readByte(){
    return bytes[offset++];
}

Memory::converted_addr Context::readAddress(){
    uint32_t val = 0;
    for (int i = 0; i < 4; ++i){
        val = (val << 8) | readByte();
    }
    return pages.convert_address(val);
}

bool Context::end() const {
    return offset >= bytes.size();
}
