#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <Analyser/Context.h>
#include <Reader/Reader.h>
#include <vector>
#include <memory>
#include <tuple>


class Output_Instrunction {
    public:
        std::string byteCode;
        std::string mnemonics;

        bool operator==(const Output_Instrunction& other) const {
            return byteCode == other.byteCode && mnemonics == other.mnemonics;
        }

    };

class Interpreter{
private:
    std::vector<Output_Instrunction> result;
    Context context;
public:
    Interpreter(Reader &Reader);
    std::vector<Output_Instrunction> interpretAll();
};

#endif
