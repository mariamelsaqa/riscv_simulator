#include "defs.h"

void blt(std::string &instruction)
{
    std::string rs2, rs1, imm_s;
    int imm;
    Three_Registers(instruction, rs1, rs2, imm_s);
    imm = stoi(imm_s);

    if (regFile[get_index(rs1)] < regFile[get_index(rs2)])
        PC += imm;
    else
        PC += 4;
}

void bge(std::string &instruction)
{
    std::string rs1, rs2, imm_s;
    int imm;
    Three_Registers(instruction, rs1, rs2, imm_s);
    imm = stoi(imm_s);

    if (regFile[get_index(rs1)] >= regFile[get_index(rs2)])
        PC += imm;
    else
        PC += 4;
}

void beq(std::string &instruction)
{
    std::string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate = stoi(imm);

    if (regFile[get_index(rs1)] == regFile[get_index(rs2)])
    {
        PC += immediate;
    }
    else
    {
        PC += 4;
    }
}

void bne(std::string &instruction)
{
    std::string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate = stoi(imm);

    if (regFile[get_index(rs1)] != regFile[get_index(rs2)])
    {
        PC += immediate;
    }
    else
    {
        PC += 4;
    }
}

void bltu(std::string &instruction)
{
    std::string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate = stoi(imm);

    if ((unsigned int)regFile[get_index(rs1)] < (unsigned int)regFile[get_index(rs2)])
    {
        PC += immediate;
    }
    else
    {
        PC += 4;
    }
}

void bgeu(std::string &instruction)
{
    std::string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate = stoi(imm);

    if ((unsigned int)regFile[get_index(rs1)] >= (unsigned int)regFile[get_index(rs2)])
    {
        PC += immediate;
    }
    else
    {
        PC += 4;
    }
}
