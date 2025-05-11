#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <cstdint>
#include <vector>

using namespace std;

namespace Memory{

    struct page_table_record{
        uint32_t page_id;
        bool is_present;
        uint32_t frame;
    };

    struct address_part{
        uint32_t value;
        uint32_t bitRate;
    };

    struct Physical_address{
        address_part frame;
        address_part offset;
    };

    struct Virtual_address{
        address_part page_id;
        address_part offset;
    };

    struct converted_addr{
        bool isValid;
        string message;
        Physical_address result;
        Virtual_address input;
    };


    class Page_Table{
    public:
        converted_addr validate_address(uint32_t address);
        Page_Table(string filename, uint32_t page_size_KB = 8, uint32_t op_size_KB = 16);
    private:
        vector<page_table_record> table = {};
        uint32_t page_size_KB;
        uint32_t op_size_KB;
        Virtual_address decode_virtual_address(uint32_t address);
        Physical_address calculate_physical_address(Virtual_address address, uint32_t frame);
    };
};
#endif