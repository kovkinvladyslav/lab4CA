#include <Reader/FileReader.h>
#include <fstream>
#include <iostream>
#include <exception>

File_Reader::File_Reader(const std::string &filename)
: filename(filename)
{
}

std::vector<uint8_t> File_Reader::get_bytes() {
    std::ifstream input_file(filename);
    std::string result_string;

    if (!(input_file).is_open()) {
        throw std::runtime_error("FileReader: error: Can't open given file !!");
    }

    std::string line;

    while(std::getline(input_file, line)){
        size_t comment_pos = line.find("//");
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
        }
        if(!line.empty()){
            result_string += line;
        }
    }
    input_file.close();
    return this->process_string(result_string);

}
