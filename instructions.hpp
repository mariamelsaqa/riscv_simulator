#pragma once
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#pragma once
#include "common.hpp"

// move to different header
std::string(instructionsHeadings[]) = {
    "add",    // 0
    "addi",   // 1
    "sub",    // 2
    "xor",    // 3
    "or",     // 4
    "xori",   // 5
    "ori",    // 6
    "andi",   // 7
    "and",    // 8
    "lb",     // 9
    "lw",     // 10
    "lh",     // 11
    "lbu",    // 12
    "lhu",    // 13
    "sb",     // 14
    "sh",     // 15
    "sw",     // 16
    "bge",    // 17
    "blt",    // 18
    "bne",    // 19
    "beq",    // 20
    "bltu",   // 21
    "bgeu",   // 22
    "slti",   // 23
    "sltiu",  // 24
    "sll",    // 25
    "slt",    // 26
    "sltu",   // 27
    "slli",   // 28
    "srli",   // 29
    "srai",   // 30
    "srl",    // 31
    "sra",    // 32
    "jal",    // 33
    "jalr",   // 34
    "lui",    // 35
    "auipc",  // 36
    "fence",  // 37
    "ecall",  // 38
    "ebreak", // 39
    "mul",    // 40
};

// u-type
extern void lui(std::string &instruction);
extern void auipc(std::string &instruction);

// j-type
extern void jal(std::string &instruction);
extern void jalr(std::string &instruction);

// memory
extern void lw(std::string &instruction);
extern void lb(std::string &instruction);
extern void lh(std::string &instruction);
extern void lbu(std::string &instruction);
extern void lhu(std::string &instruction);
extern void sb(std::string &instruction);
extern void sh(std::string &instruction);
extern void sw(std::string &instruction);

// B-type
extern void beq(std::string &instruction);
extern void bne(std::string &instruction);
extern void bltu(std::string &instruction);
extern void bgeu(std::string &instruction);
extern void blt(std::string &instruction);
extern void bge(std::string &instruction);

// I-type
extern void addi(std::string &instruction);
extern void xori(std::string &instruction);
extern void slti(std::string &instruction);
extern void sltiu(std::string &instruction);
extern void ori(std::string &instruction);
extern void andi(std::string &instruction);
extern void slli(std::string &instruction);
extern void srli(std::string &instruction);
extern void srai(std::string &instruction);

// R-type
extern void add(std::string &instruction);
extern void sub(std::string &instruction);
extern void sll(std::string &instruction);
extern void slt(std::string &instruction);
extern void sltu(std::string &instruction);
extern void x_or(std::string &instruction);
extern void srl(std::string &instruction);
extern void sra(std::string &instruction);
extern void or_instruction(std::string &instruction);
extern void and_instruction(std::string &instruction);

// M-extension
extern void mul(std::string &instruction);
extern void mulH(std::string &instruction);
extern void mulHU(std::string &instruction);
extern void mulHSU(std::string &instruction);
extern void div(std::string &instruction);
extern void divu(std::string &instruction);
extern void rem(std::string &instruction);
extern void remu(std::string &instruction);

#endif // INSTRUCTIONS_H