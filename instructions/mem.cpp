#include "defs.h"

void lw(std::string &instruction)
{
    std::string rd, rs1;
    int offset;
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    for (int i = 0; i < stored_adresses.size(); i++)
    {
        if (stored_adresses[i] == address)
        {
            regFile[get_index(rd)] = stored_values[i];
        }
    }
    PC = PC + 4;
}

void sb(std::string &instruction)
{
    bool flag = false;
    std::string rd, rs1;
    int offset;
    std::string final_bin = "";
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    std::string binary = dec_to_binary(regFile[get_index(rd)]);
    while (binary.size() < 32)
    {
        binary = '0' + binary;
    }
    for (int i = 23; i < 32; i++)
    {
        final_bin = final_bin + binary[i];
    }
    for (int i = 0; i < stored_adresses.size(); i++)
    {
        if (stored_adresses[i] == address)
        {
            stored_values[i] = binary_to_dec(final_bin);
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        stored_adresses.push_back(address);
        stored_values.push_back(binary_to_dec(final_bin));
    }
    PC += 4;
}

void sh(std::string &instruction)
{
    bool flag = false;
    std::string rd, rs1;
    int offset;
    std::string final_bin = "";

    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;

    std::string binary = dec_to_binary(regFile[get_index(rd)]);
    while (binary.size() < 32)
    {
        binary = '0' + binary;
    }
    for (int i = 15; i < 32; i++)
    {
        final_bin = final_bin + binary[i];
    }
    for (int i = 0; i < stored_adresses.size(); i++)
    {
        if (stored_adresses[i] == address)
        {
            stored_values[i] = binary_to_dec(final_bin);
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        stored_adresses.push_back(address);
        stored_values.push_back(binary_to_dec(final_bin));
    }
    PC += 4;
}

void sw(std::string &instruction)
{
    bool flag = false;
    std::string rd, rs1;
    int offset;
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    for (int i = 0; i < stored_adresses.size(); i++)
    {
        if (stored_adresses[i] == address)
        {
            stored_values[i] = regFile[get_index(rd)];
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        stored_adresses.push_back(address);
        stored_values.push_back(regFile[get_index(rd)]);
    }
    PC = PC + 4;
}

void lb(std::string &instruction)
{
    std::string rd, rs1;
    int offset;
    std::string final_bin = "";
    int number;

    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;

    for (int i = 0; i < stored_adresses.size(); i++)
        if (stored_adresses[i] == address)
            number = stored_values[i];

    std::string binary = dec_to_binary(number);
    while (binary.size() < 32)
    {
        binary = '0' + binary;
    }
    for (int i = 23; i < 32; i++)
        final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = binary_to_dec(final_bin);
    PC += 4;
}

void lh(std::string &instruction)
{
    std::string rd, rs1;
    int offset;
    std::string final_bin = "";
    int number;

    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    for (int i = 0; i < stored_adresses.size(); i++)
        if (stored_adresses[i] == address)
            number = stored_values[i];
    std::string binary = dec_to_binary(number);
    while (binary.size() < 32)
    {
        binary = '0' + binary;
    }
    for (int i = 15; i < 32; i++)
        final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = binary_to_dec(final_bin);

    PC += 4;
}

void lbu(std::string &instruction)
{
    std::string rd, rs1;
    int offset;
    std::string final_bin = "";
    int number;

    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;

    for (int i = 0; i < stored_adresses.size(); i++)
        if (stored_adresses[i] == address)
            number = stored_values[i];

    int temp = number << 24 >> 24;
    // std::string binary = dec_to_binary(number);
    // while(binary.size() < 32)
    // {
    //   binary = '0' + binary;
    // }
    // for(int i = 23; i < 32; i++)
    //   final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = temp;

    PC += 4;
}

void lhu(std::string &instruction)
{
    std::string rd, rs1;
    int offset;
    std::string final_bin = "";
    int number;

    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;

    for (int i = 0; i < stored_adresses.size(); i++)
        if (stored_adresses[i] == address)
            number = stored_values[i];

    int temp = number << 16 >> 16;
    // std::string binary = dec_to_binary(number);
    // while(binary.size() < 32)
    // {
    //   binary = '0' + binary;
    // }
    // for(int i = 23; i < 32; i++)
    //   final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = temp;

    PC += 4;
}
