#include <Memory/Memory.h>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <math.h>
#include <algorithm>

using namespace Memory;
using namespace std;



Page_Table::Page_Table(string filename, uint32_t page_size_KB, uint32_t op_size_KB)
    :  page_size_KB(page_size_KB),
        op_size_KB(op_size_KB)
{   
    ifstream file(filename);
    
    if (!file.is_open()) {
        runtime_error("Failed to open file: " + filename + "\n");
        return;
    }
    string line;
    vector<vector<string>> str_data;
    while (getline(file, line)) {
        vector<string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        str_data.push_back(row);
    }
    for(vector<string> row : str_data){
        page_table_record record;

        if(row.size() != 3){
            runtime_error("Page File should have 3 columns");
            return;
        }
        record.page_id = static_cast<uint32_t>(stoul(row[0]));
        record.is_present = row[1] == "1" ? 1 : 0;
        record.frame = static_cast<uint32_t>(stoul(row[2]));
        table.push_back(record);
    }

    file.close();


}

converted_addr Page_Table::validate_address(uint32_t address){
    Virtual_address input_address = decode_virtual_address(address);

    auto record = find_if(table.begin(), table.end(), [&](page_table_record row){
        return row.page_id == input_address.page_id.value;
    });
    
    if(record == table.end()){
        return {false, "failed to convert: page " + to_string(input_address.page_id.value)
                        + " does not exist"};
    }

    if(!record->is_present){
        return {false, "failed to convert: page" + to_string(input_address.page_id.value) 
            + " is not present in memory"};
    }
    Physical_address calculated_address = calculate_physical_address(input_address, record->frame);
    return {true, "success", calculated_address, input_address};
}

Virtual_address Page_Table::decode_virtual_address(uint32_t address){
    Virtual_address input_address;
    input_address.offset.bitRate = log2(page_size_KB * 1024);
    input_address.page_id.bitRate = 32 - input_address.offset.bitRate;
    input_address.page_id.value = address >> input_address.offset.bitRate;
    input_address.offset.value = address & UINT32_MAX >> input_address.page_id.bitRate;
    return input_address;
}

Physical_address Page_Table::calculate_physical_address(Virtual_address address, uint32_t frame){
    Physical_address calculated_addr;
    calculated_addr.frame.value = frame;
    calculated_addr.offset.bitRate = address.offset.bitRate;
    calculated_addr.offset.value = address.offset.value;
    calculated_addr.frame.bitRate = 32 - calculated_addr.offset.bitRate;
    return calculated_addr;
}

