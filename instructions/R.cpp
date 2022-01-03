#include "defs.h"

void add(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] + regFile[get_index(rs2)];
    PC += 4;
}

void sub(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] - regFile[get_index(rs2)];
    PC += 4;
}

void sll(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] << regFile[get_index(rs2)];
    PC += 4;
}

void slt(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    if (regFile[get_index(rs1)] < regFile[get_index(rs2)])
        regFile[get_index(rd)] = 1;
    else
        regFile[get_index(rd)] = 0;
    PC += 4;
}

void sltu(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] << (unsigned int)regFile[get_index(rs2)];
    PC += 4;
}

void _xor(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] ^ regFile[get_index(rs2)];
    PC += 4;
}

void srl(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] >> regFile[get_index(rs2)];
    PC += 4;
}

void sra(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)regFile[get_index(rs2)];
    PC += 4;
}

void _or(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] | regFile[get_index(rs2)];
    PC += 4;
}

void _and(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    regFile[get_index(rd)] = regFile[get_index(rs1)] & regFile[get_index(rs2)];
    PC += 4;
}
