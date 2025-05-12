#ifndef VARIANT_TEST_H
#define VARIANT_TEST_H

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <Reader/StringReader.h>
#include <Analyser/Interpreter.h>

class Variant10Test : public ::testing::Test {
protected:
    std::string pageFileName = "../../data/pages.csv";
    void TestInstruction(const std::string& hexCode, const std::string& expectedMnemonic) {
        String_Reader reader(hexCode);

        Interpreter interpreter(reader, pageFileName);
        auto result = interpreter.interpretAll();

        

        ASSERT_EQ(result.size(), 1);
        EXPECT_EQ(result[0].mnemonics, expectedMnemonic);
        EXPECT_EQ(result[0].byteCode, hexCode);
    }

    void TestMultipleInstructions(const std::string& input, const std::vector<Output_Instrunction>& expected) {
        String_Reader reader(input);

        Interpreter interpreter(reader, pageFileName);
        auto result = interpreter.interpretAll();

        EXPECT_EQ(result, expected);
    }

    void TestInstructionThrows(const std::string& input) {
        String_Reader reader(input);

        EXPECT_THROW({
            Interpreter interpreter(reader, pageFileName);
            interpreter.interpretAll();
        }, std::runtime_error);
    }
};

#endif