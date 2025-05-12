#include <gtest/gtest.h>
#include <Reader/StringReader.h>
#include <Reader/FileReader.h>
#include <Analyser/Interpreter.h>
#include <fstream>
#include <sstream>
#include <IntegrationTestFixture.h>
#include <TestUtils.h>

TEST_F(IntegrationTestFixture, StringReader_BasicCommand) {
    std::string input = "1A 12";

    auto result = InterpretString(input);

    std::vector<Output_Instrunction> expected = { {"1A 12", "MOV R1, R2"} };
    EXPECT_EQ(result, expected);
}

TEST_F(IntegrationTestFixture, FileReader_BasicCommand) {
    std::string input = "1A 12";

    auto result = InterpretFile(input);

    std::vector<Output_Instrunction> expected = { {"1A 12", "MOV R1, R2"} };
    EXPECT_EQ(result, expected);
}

TEST_F(IntegrationTestFixture, FileReader_HandlesComments) {
    std::string input = "1A 12 // comment\n1C 01 33 // comment";

    auto result = InterpretFile(input);

    std::vector<Output_Instrunction> expected = {
        {"1A 12", "MOV R1, R2"},
        {"1C 01 33", "MOV R1, 33"}
    };
    EXPECT_EQ(result, expected);
}

TEST_F(IntegrationTestFixture, InvalidHexCharacters) {
    EXPECT_THROW({
        InterpretString("1A XZ");
    }, std::runtime_error);
}

TEST_F(IntegrationTestFixture, IncompleteHexPairThrows) {
    EXPECT_THROW({
        try {
            InterpretString("1A 1");
        } catch (const std::runtime_error& e) {
            EXPECT_NE(std::string(e.what()).find("Incomplete hex pair"), std::string::npos);
            throw;
        }
    }, std::runtime_error);
}

TEST_F(IntegrationTestFixture, FileReader_NonExistentFileThrows) {
    EXPECT_THROW({
        File_Reader reader("this_file_should_not_exist.txt");
        Interpreter interpreter(reader, csvFileName);
    }, std::runtime_error);
}

TEST_F(IntegrationTestFixture, StringReader_EmptyStringReturnsNothing) {
    std::string input = "";
    std::vector<Output_Instrunction> expected = {};
    auto result = InterpretString(input);
    EXPECT_EQ(result, expected);
}

TEST_F(IntegrationTestFixture, FileReader_EmptyFileReturnsNothing) {
    std::vector<Output_Instrunction> result = {};
    EXPECT_EQ(InterpretFile(""), result);
}

TEST_F(IntegrationTestFixture, FileReader_OnlyCommentsReturnsNothing) {
    std::string input = "// This is a comment\n// Another comment";
    std::vector<Output_Instrunction> expected = {};
    auto result = InterpretFile(input);
    EXPECT_EQ(result, expected);
}

TEST_F(IntegrationTestFixture, FileReader_MixedCommentsAndEmptyLines) {
    std::string input =
        "// comment\n"
        "\n"
        "1A 12\n"
        "\n"
        "// another comment\n"
        "1C 01 33\n";

    std::vector<Output_Instrunction> expected = {
        {"1A 12", "MOV R1, R2"},
        {"1C 01 33", "MOV R1, 33"}
    };

    auto result = InterpretFile(input);
    EXPECT_EQ(result, expected);
}


