#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "std++.hpp"
#include "instruction.hpp"

extern std::array<int, 32> regFile;
extern unsigned int PC;
extern int MAX_PC;
extern int starting_address;
extern std::vector<int> stored_adresses;
extern std::vector<int> stored_values;
extern const std::map<std::string, std::string> Registers;
extern std::string path;
extern std::string path2;

#endif