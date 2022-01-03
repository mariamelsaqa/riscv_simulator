#include "defs.h"

void slti(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    if (regFile[get_index(rs1)] < imm)
        regFile[get_index(rd)] = 1;
    else
        regFile[get_index(rd)] = 0;
    PC += 4;
}

void sltiu(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    if (regFile[get_index(rs1)] < imm)
        regFile[get_index(rd)] = 1;
    else
        regFile[get_index(rd)] = 0;
    PC += 4;
}

void ori(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    regFile[get_index(rd)] = regFile[get_index(rs1)] | imm;
    PC += 4;
}

void andi(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    regFile[get_index(rd)] = regFile[get_index(rs1)] & imm;
    PC += 4;
}

void slli(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    regFile[get_index(rd)] = regFile[get_index(rs1)] << imm;
    PC += 4;
}

void srli(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    regFile[get_index(rd)] = regFile[get_index(rs1)] >> imm;
    PC += 4;
}

void srai(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)imm;
    PC += 4;
}

void addi(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);
    regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
    PC += 4;
}

void xori(std::string &instruction)
{
    std::string rd, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1, imm_s);
    imm = stoi(imm_s);

    regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
    PC += 4;
}