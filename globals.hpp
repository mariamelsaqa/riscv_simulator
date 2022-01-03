#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "std++.hpp"
#include "instruction.hpp"

extern std::string path;
extern std::string path2;

extern unsigned int PC;
extern int MAX_PC;
extern int starting_address;
extern std::vector<int> stored_adresses;
extern std::vector<int> stored_values;

extern std::array<int, 32> regFile;
extern const std::map<std::string, std::string> regNames;

extern std::vector<Instruction> inst_mem;
extern const std::string instNames[];
extern const std::map<std::string, int> instOps;
extern const std::map<int, instFunc_t> instMap;

#endif