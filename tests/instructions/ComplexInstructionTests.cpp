#include "Variant10Test.h"

TEST_F(Variant10Test, MultipleInstructions) {
    std::vector<Output_Instrunction> expected = {
        {"1A 12", "MOV R1, R2"},
        {"1B 05 00 C0 00 A1", "MOV R5, [0x00C000A1]"},
        {"90 0A", "JMP A"}
    };

    TestMultipleInstructions("1A 12 1B 05 00 C0 00 A1 90 0A", expected);
}

TEST_F(Variant10Test, InvalidInstructionCode) {
    TestInstructionThrows("FF 01 02");
}
