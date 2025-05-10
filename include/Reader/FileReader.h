#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <cstdint>
#include <vector>
#include <Reader/Reader.h>

class File_Reader : public Reader {
    const std::string &filename;
    public:
    File_Reader(const std::string &filename);
    std::vector<uint8_t> get_bytes() override;
};


#endif
