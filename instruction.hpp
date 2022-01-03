
#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include "std++.hpp"
struct Instruction
{
    std::string input;
};

typedef void (*instFunc_t)(std::string &str);

#endif