#include "Variant10Test.h"

TEST_F(Variant10Test, MovRegToReg) {
    TestInstruction("1A 34", "MOV R3, R4");
}

TEST_F(Variant10Test, MovMemToReg) {
    TestInstruction("1B 05 00 C0 00 A1", "MOV R5, [0x000020A1]");
}


TEST_F(Variant10Test, AddRegRegReg) {
    TestInstruction("03 01 23", "ADD R1, R2, R3");
}

TEST_F(Variant10Test, AddRegRegMem) {
    TestInstruction("04 12 00 C0 00 A1", "ADD R1, R2, [0x000020A1]");
}


TEST_F(Variant10Test, MulRegRegReg) {
    TestInstruction("21 01 23", "MUL R1, R2, R3");
}


TEST_F(Variant10Test, MulRegRegMem) {
    TestInstruction("23 12 00 C0 00 A1", "MUL R1, R2, [0x000020A1]");
}


TEST_F(Variant10Test, JmpShift) {
    TestInstruction("90 0A", "JMP A");
}

TEST_F(Variant10Test, JmpWithNegativeShift) {
    TestInstruction("90 EF", "JMP -11");
}

TEST_F(Variant10Test, JmpAddr) {
    TestInstruction("91 FF FF FF 00", "JMP [0x00001F00]");
}

TEST_F(Variant10Test, MovLit8ToReg_Positive) {
    TestInstruction("1C 01 33", "MOV R1, 33");
}

TEST_F(Variant10Test, MovLit8ToReg_Negative) {
    TestInstruction("1C 01 CD", "MOV R1, -33");
}


TEST_F(Variant10Test, AccessMissingPage) {
    TestInstruction("1B 05 00 00 00 A1", "failed to convert: page 0 does not exist");
}

TEST_F(Variant10Test, AccessNotLoadedPage) {
    TestInstruction("1B 05 00 00 20 A1", "failed to convert: page 1 is not present in memory");
}
