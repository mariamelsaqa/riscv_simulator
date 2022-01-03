#include "defs.h"
#include "ops.hpp"
#include "std++.hpp"

void print_all_bases(int num, std::ostream &outs)
{
    outs << "Dec: " << std::dec << num << "   "
         << "Hex: " << std::hex << num << "   "
         << "Bin: " << dec_to_binary(num) << std::endl;
}

void print_regfile(std::ostream &outs)
{
    outs << "Reg File contents after instruction " << ((PC - starting_address) / 4) << std::endl;
    for (int i = 0; i < 32; i++)
    {
        outs << "x" << std::dec << i << "---> ";
        print_all_bases(regFile[i], outs);
    }
    outs << std::endl;
}
void print_data_memory(std::ostream &outs)
{
    outs << "-------------Memory Content-------------" << std::endl;
    for (int i = 0; i < stored_adresses.size(); i++)
        print_all_bases(stored_values[i], outs);

    outs << "----------------------------" << std::endl
         << std::endl;
}

void print_inst_memory(std::ostream &outs)
{
    for (int i = 0; i < inst_mem.size(); i++)
        outs << inst_mem[i].input << std::endl;

    outs << std::endl;
}
bool isNumber(std::string line)
{
    char *p;
    std::strtol(line.c_str(), &p, 10);
    return *p == 0;
}
void throw_err(const std::string &err)
{
    std::cerr << err << std::endl;
    exit(EXIT_FAILURE);
}

std::string toupper(const std::string &str)
{
    std::string upper = str;
    for (auto &c : upper)
        c = toupper(c);
    return upper;
}
std::string tolower(const std::string &str)
{
    std::string lower = str;
    for (auto &c : lower)
        c = tolower(c);
    return lower;
}
// utils
int binary_to_dec(std::string input)
{
    int binary = std::stoi(input);
    int decimal = 0;
    int rem = 0;

    for (int i = 0; binary > 0; i++)
    {
        rem = binary % 10;
        decimal += rem * pow(2, i);
        binary = binary / 10;
    }

    return decimal;
}
// utils
std::string dec_to_binary(int number)
{
    int binary[8];
    std::string temp = "";

    for (int i = 0; i < 8; i++)
        binary[i] = 0;

    for (int i = 0; number > 0; i++)
    {
        binary[7 - i] = number % 2;
        number = number / 2;
    }

    for (int i = 0; i < 8; i++)
        temp += std::to_string(binary[i]);

    return temp;
}
int get_index(const std::string &reg)
{
    std::string temp = reg;
    temp = temp.substr(1, temp.size());
    return std::stoi(temp);
}
int getInstOp(const std::string &instName)
{
    std::string lower = tolower(instName);
    auto findOp = instOps.find(lower);
    if (findOp == instOps.end())
        return UNKNOWN_OP;
    return findOp->second;
}
