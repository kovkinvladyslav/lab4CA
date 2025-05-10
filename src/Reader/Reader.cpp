#include <Reader/Reader.h>

#include <iostream>
std::vector<uint8_t> Reader::process_string(const std::string &input_string){
    if(input_string.empty()){
        return {};
    }

    std::vector<uint8_t> byte_source;
    for(size_t i = 0; i < input_string.length(); i++){
        char symbol = input_string[i];
        if(std::isxdigit(symbol)){
            if(i + 1 >= input_string.length()) {
                throw std::runtime_error("Error: Incomplete hex pair at the end of string");
            }

            char next_symbol = input_string[++i];
            if(std::isxdigit(next_symbol)){
                std::string byte_str = {symbol, next_symbol};
                byte_source.push_back(static_cast<uint8_t>(std::stoi(byte_str, nullptr, 16)));
            } else {
                std::string error_out = "Error at position " + std::to_string(i - 1)
                    + ": expected two hex digits, but found '" + symbol
                    + "' followed by non-hex character '" + next_symbol
                    + "'.\nFormat should be like 'A1', '3F', '00', etc.\n";
                throw std::runtime_error(error_out);
            }
        } else if(symbol != ' ' && symbol != '\n' && symbol != '\t' && symbol != '\r'){
            if(symbol == '/'){
                throw std::runtime_error("Reader: Comments are not allowed in strings");
            } else {
                throw std::runtime_error("Reader: Illigal Character Encountered");
            }
        }
    }
    return byte_source;
}
