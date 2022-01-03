#ifndef UTILS_H
#define UTILS_H
#pragma once
#include "common.hpp"
// utils
extern bool isNumber(std::string line);
extern int binary_to_dec(std::string input);
extern std::string dec_to_binary(int number);
extern int get_index(const std::string &reg);

#endif // UTILS_H