#include <Reader/StringReader.h>
#include <vector>

String_Reader::String_Reader(const std::string &input_string) : hexString(input_string)
    {}

std::vector<uint8_t> String_Reader::get_bytes() {
    return process_string(hexString);
}
