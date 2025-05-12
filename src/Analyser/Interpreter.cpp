#include <Reader/Reader.h>
#include <vector>
#include <memory>
#include <Analyser/Interpreter.h>
#include <stdexcept>

Interpreter::Interpreter(Reader &reader, std::string pageFile)
    : context(reader.get_bytes(), pageFile) {}

std::string formatAsBytes(uint32_t value) {
    char bytesFormat[20];
    sprintf(bytesFormat, "%02X %02X %02X %02X",
            (value >> 24) & 0xFF,
            (value >> 16) & 0xFF,
            (value >> 8) & 0xFF,
            value & 0xFF);
    return std::string(bytesFormat);
}


std::string formatAddressAsHex(uint32_t value) {
    char hexFormat[20];
    sprintf(hexFormat, "[0x%08X]", value);
    return std::string(hexFormat);
}

std::string hexValue(uint8_t value) {
    char hexFormat[3];
    sprintf(hexFormat, "%X", value);
    return std::string(hexFormat);
}

std::string hexByte(uint8_t value) {
    char hexFormat[3];
    sprintf(hexFormat, "%02X", value);
    return std::string(hexFormat);
}

std::string getRegisterName(uint8_t reg) {
    return "R" + hexValue(reg);
}

void createOutput(std::vector<Output_Instrunction>& result, const std::string& rawBytes, const std::string& mnemonic) {
    result.push_back({rawBytes, mnemonic});
}

std::string formatAsBytes(Memory::Virtual_address address){
    uint32_t solid_address = 0;
    solid_address = (solid_address | address.page_id.value) << address.offset.bitRate;
    solid_address |= address.offset.value;
    return formatAsBytes(solid_address);
}

std::string formatAddressAsHex(Memory::Physical_address address){
    uint32_t solid_address = 0;
    solid_address = (solid_address | address.frame.value) << address.offset.bitRate;
    solid_address = solid_address | address.offset.value;
    return formatAddressAsHex(solid_address);
}

std::vector<Output_Instrunction> Interpreter::interpretAll() {
    std::vector<Output_Instrunction> result;

    while (!context.end()) {
        uint8_t opcode = context.readByte();

        switch (opcode) {
        case 0x1A: {
            uint8_t srcReg = context.readByte();
            uint8_t dstReg = srcReg & 0x0F;
            srcReg >>= 4;
            createOutput(
                result,
                "1A " + hexValue(srcReg) + hexValue(dstReg),
                "MOV " + getRegisterName(srcReg) + ", " + getRegisterName(dstReg));
            break;
        }
        case 0x1B: {
            uint8_t arg = context.readByte();
            if ((arg >> 4) != 0x0) break;
            uint8_t reg = arg & 0x0F;
            auto address = context.readAddress();
            std::string out_raw = "1B 0" + hexValue(reg) + " " + formatAsBytes(address.input);
            std::string out_mnem;
            if(address.isValid){
                out_mnem = "MOV " + getRegisterName(reg) + ", " + formatAddressAsHex(address.result);
            } else {
                out_mnem = address.message;
            }

            createOutput(
                result,
                out_raw, 
                out_mnem 
            );
            break;
            
        }
        case 0x03: {
            uint8_t arg = context.readByte();
            if ((arg >> 4) != 0x0) break;
            uint8_t dstReg = arg & 0x0F;
            uint8_t srcReg1 = context.readByte();
            uint8_t srcReg2 = srcReg1 & 0x0F;
            srcReg1 >>= 4;
            createOutput(
                result,
                "03 0" + hexValue(dstReg) + " " + hexValue(srcReg1) + hexValue(srcReg2),
                "ADD " + getRegisterName(dstReg) + ", " + getRegisterName(srcReg1) + ", " + getRegisterName(srcReg2));
            break;
        }
        case 0x04: {
            uint8_t dstReg = context.readByte();
            uint8_t srcReg = dstReg & 0x0F;
            dstReg >>= 4;
            auto address = context.readAddress();
            createOutput(
                result,
                "04 " + hexValue(dstReg) + hexValue(srcReg) + " " + formatAsBytes(address.input),
                address.isValid ? "ADD " + getRegisterName(dstReg) + ", " + getRegisterName(srcReg) + ", " + formatAddressAsHex(address.result)
                                : address.message);
            break;
        }
        case 0x21: {
            uint8_t arg = context.readByte();
            if ((arg >> 4) != 0) break;
            uint8_t dstReg = arg & 0x0F;
            uint8_t srcReg1 = context.readByte();
            uint8_t srcReg2 = srcReg1 & 0x0F;
            srcReg1 >>= 4;
            createOutput(
                result,
                "21 0" + hexValue(dstReg) + " " + hexValue(srcReg1) + hexValue(srcReg2),
                "MUL " + getRegisterName(dstReg) + ", " + getRegisterName(srcReg1) + ", " + getRegisterName(srcReg2));
            break;
        }
        case 0x23: {
            uint8_t dstReg = context.readByte();
            uint8_t srcReg = dstReg & 0x0F;
            dstReg >>= 4;
            auto address = context.readAddress();
            createOutput(
                result,
                "23 " + hexValue(dstReg) + hexValue(srcReg) + " " + formatAsBytes(address.input),
                address.isValid ? "MUL " + getRegisterName(dstReg) + ", " + getRegisterName(srcReg) + ", " + formatAddressAsHex(address.result)
                                : address.message
            );
            break;
        }
        case 0x90: {
            int8_t shiftVal = static_cast<int8_t>(context.readByte());
            int8_t shiftValMnem = shiftVal;
            std::string mnemOut = "JMP ";
            if(shiftValMnem < 0){
                shiftValMnem = -shiftValMnem;
                mnemOut += "-";
            }
            createOutput(
                result,
                "90 " + hexByte(shiftVal),
                mnemOut + hexValue(shiftValMnem)
            );
            break;
        }
        case 0x91: {
            auto address = context.readAddress();
            createOutput(
                result,
                "91 " + formatAsBytes(address.input),
                address.isValid ? "JMP " + formatAddressAsHex(address.result) : address.message
            );
            break;
        }
        case 0x1C: {
            uint8_t arg = context.readByte();
            if((arg >> 4) != 0) break;
            uint8_t srcReg = arg & 0x0F;
            int8_t lit8 = static_cast<int8_t>(context.readByte());
            int8_t lit8Mnem = lit8;
            std::string mnemOutput = "MOV " + getRegisterName(srcReg) + ", ";
            if (lit8Mnem < 0) {
                lit8Mnem = -lit8Mnem;
                mnemOutput += "-";
            };
            createOutput(
                result,
                "1C 0" + hexValue(srcReg) + " " + hexByte(lit8),
                mnemOutput + hexValue(lit8Mnem)
            );
            break;
        }
        default:
            throw std::runtime_error("Invalid instruction code !");
            break;
        }
    }

    return result;
}
