#ifndef READER_H
#define READER_H

#include <string>
#include <cstdint>
#include <vector>

class Reader {
protected:
    std::vector<uint8_t> process_string(const std::string &input_string);
public:
    virtual std::vector<uint8_t> get_bytes() = 0;
    ~Reader() = default;
};


#endif
