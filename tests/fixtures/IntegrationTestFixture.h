#ifndef INTEGRATION_TEST
#define INTEGRATION_TEST


#include <gtest/gtest.h>
#include <Reader/StringReader.h>
#include <Reader/FileReader.h>
#include <Analyser/Interpreter.h>
#include <fstream>
#include <sstream>
#include <TestUtils.h>

class IntegrationTestFixture : public ::testing::Test {
protected:
    std::string csvFileName = "../../data/pages.csv";
    
    std::vector<Output_Instrunction> InterpretString(const std::string& input) {
        String_Reader reader(input);
        Interpreter interpreter(reader, csvFileName);
        return interpreter.interpretAll();
    }

    std::vector<Output_Instrunction> InterpretFile(const std::string& content) {
        std::string fileName = createTempFile(content);
        File_Reader reader(fileName);
        Interpreter interpreter(reader, csvFileName);
        auto result = interpreter.interpretAll();

        removeTempFile(fileName);

        return result;
    }
};

#endif