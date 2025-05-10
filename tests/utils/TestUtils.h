#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <sstream>
#include <Reader/StringReader.h>
#include <Reader/FileReader.h>
#include <Analyser/Interpreter.h>

void PrintTo(const Output_Instrunction& instr, std::ostream* os) {
    *os << "{ byteCode: \"" << instr.byteCode << "\", mnemonics: \"" << instr.mnemonics << "\" }";
}

std::string createTempFile(const std::string& content) {
    std::string tempFileName = "temp_test_file.txt";
    std::ofstream outFile(tempFileName);
    outFile << content;
    outFile.close();
    return tempFileName;
}

void removeTempFile(const std::string& fileName) {
    std::remove(fileName.c_str());
}

#endif