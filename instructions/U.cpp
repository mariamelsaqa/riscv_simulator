#include "defs.h"

void lui(std::string &instruction)
{
    std::string rd, imm_s;
    Register_imm(instruction, rd, imm_s);
    int imm = stoi(imm_s);
    // int temp = imm * 4096; // shift 12 bits
    // regFile[get_index(rd)] = regFile[get_index(rd)] + temp;
    regFile[get_index(rd)] = regFile[get_index(rd)] + (imm << 12);
    PC += 4;
}

void auipc(std::string &instruction)
{
    std::string rd, imm_s;
    Register_imm(instruction, rd, imm_s);
    int imm = stoi(imm_s);
    regFile[get_index(rd)] = (imm * 4096) + PC; // shift 12 bits
    PC += 4;
}
