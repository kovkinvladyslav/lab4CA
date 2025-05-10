#ifndef STRING_READER_H
#define STRING_READER_H
#include <Reader/Reader.h>


class String_Reader : public Reader {
    private:
    const std::string &hexString;
    public:
    String_Reader(const std::string &input_string);
    std::vector<uint8_t> get_bytes() override;
};

#endif
