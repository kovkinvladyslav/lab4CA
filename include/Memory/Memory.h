#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <cstdint>

namespace Memory{
    struct access_result{
        bool isValid;
        std::string message;
    };

    struct page_table_record{
        char page_id[19];

    };

    class Reader{
    public:
        access_result validate_address(uint32_t address);
    private:
        
    };
};



#endif