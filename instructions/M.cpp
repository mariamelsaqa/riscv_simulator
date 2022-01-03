#include "defs.h"

void mul(std::string &instruction)
{
    std::string rd, rs1, rs2;
    // std::cout << "WE ARE HERE" << std::endl;
    Three_Registers(instruction, rd, rs1, rs2);

    long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
    regFile[get_index(rd)] = x & (0x00000000FFFFFFFF);

    PC += 4;
}

void mulH(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
    regFile[get_index(rd)] = x >> 32;

    PC += 4;
}

void mulHU(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    unsigned long int x = (unsigned long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
    regFile[get_index(rd)] = x >> 32;

    PC += 4;
}

void mulHSU(std::string &instruction)
{
    std::string rd, rs1, rs2;
    Three_Registers(instruction, rd, rs1, rs2);

    unsigned long int x = (signed long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
    regFile[get_index(rd)] = x >> 32;

    PC += 4;
}

void div(std::string &instruction)
{
    std::string rd, rs1, rs2;
    int result;
    Three_Registers(instruction, rd, rs1, rs2);

    if (regFile[get_index(rs2)] == 0)
    { // dividing by zero
        result = -1;
    }
    else if (regFile[get_index(rs1)] == 0x80000000 && regFile[get_index(rs2)] == -1)
    {                        // overflow
        result = 0x80000000; //-2^XLEN-1
    }
    else
    {
        result = regFile[get_index(rs1)] / regFile[get_index(rs2)];
    }

    regFile[get_index(rd)] = result;

    PC += 4;
}

void divu(std::string &instruction)
{
    std::string rd, rs1, rs2;
    unsigned int result;
    Three_Registers(instruction, rd, rs1, rs2);

    if (regFile[get_index(rs2)] == 0)
    {                        // dividing by zero
        result = 0xFFFFFFFF; //(2^XLen)-1
    }
    else
    {
        result = (unsigned int)regFile[get_index(rs1)] / (unsigned int)regFile[get_index(rs2)];
    }

    regFile[get_index(rd)] = result;

    PC += 4;
}

void rem(std::string &instruction)
{
    std::string rd, rs1, rs2;
    int result;
    Three_Registers(instruction, rd, rs1, rs2);

    if (regFile[get_index(rs2)] == 0)
    {
        result = regFile[get_index(rs1)];
    }
    else if (regFile[get_index(rs1)] == 0x80000000 && regFile[get_index(rs2)] == -1)
    {
        result = 0;
    }
    else
    {
        result = regFile[get_index(rs1)] % regFile[get_index(rs2)];
    }

    regFile[get_index(rd)] = result;

    PC += 4;
}

void remu(std::string &instruction)
{
    std::string rd, rs1, rs2;
    unsigned int result;
    Three_Registers(instruction, rd, rs1, rs2);

    if (regFile[get_index(rs2)] == 0)
    {
        result = regFile[get_index(rs1)];
    }
    else
    {
        result = (unsigned int)regFile[get_index(rs1)] % (unsigned int)regFile[get_index(rs2)];
    }

    regFile[get_index(rd)] = result;

    PC += 4;
}
