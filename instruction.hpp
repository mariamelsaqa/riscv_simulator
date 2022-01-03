
#ifndef INSTRUCTIONS_HPP
#define INSTRUCTION_HPP
#include "std++.hpp"
struct Instruction
{
    std::string input;
};

typedef void (*instFunc)(std::string &str);

extern std::string instructionsHeadings[];
extern const std::map<int, instFunc> instMap;

#endif