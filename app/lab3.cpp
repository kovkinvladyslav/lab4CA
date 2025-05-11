#include <iostream>
#include <fstream>
#include <Reader/FileReader.h>
#include <Analyser/Interpreter.h>

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cout << "Usage: lab3 <path to the file>" << std::endl;
        return 1;
    }
    std::string filname = argv[1];
    File_Reader reader(filname);
    Interpreter interpreter(reader, "../../data/pages.csv");
    auto result = interpreter.interpretAll();

    for(auto resultNode : result){
        std::cout << resultNode.byteCode << "\n" << resultNode.mnemonics << "\n\n";
    }

    return 0;
}
