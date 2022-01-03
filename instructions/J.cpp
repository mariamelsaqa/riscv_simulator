#include "defs.h"

void jal(std::string &instruction)
{
    std::string rd, imm_s;
    Register_imm(instruction, rd, imm_s);
    int imm = stoi(imm_s);
    regFile[get_index(rd)] = PC + 4;
    PC += imm;
}

void jalr(std::string &instruction)
{
    std::string rd, rs1;
    int offset;
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    regFile[get_index(rd)] = PC + 4;
    PC = regFile[get_index(rs1)] + offset;
}
