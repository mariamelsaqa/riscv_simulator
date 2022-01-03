#include "globals.hpp"
#include "ops.hpp"
#include "defs.h"

std::string path = "Test.txt";
std::string path2 = "Data.txt";

std::array<int, 32> regFile;
unsigned int PC = 0;
int MAX_PC;
int starting_address = 0;
std::vector<int> stored_adresses;
std::vector<int> stored_values;

std::string instructionsHeadings[] = {
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

const std::map<int, instFunc> instMap{{ADD, &add},
                                      {ADDI, &addi},
                                      {SUB, &sub},
                                      {XOR, &_xor},
                                      {OR, &_or},
                                      {XORI, &xori},
                                      {ORI, &ori},
                                      {ANDI, &andi},
                                      {AND, &_and},
                                      {LB, &lb},
                                      {LW, &lw},
                                      {LH, &lh},
                                      {LBU, &lbu},
                                      {LHU, &lhu},
                                      {SB, &sb},
                                      {SH, &sh},
                                      {SW, &sw},
                                      {BGE, &bge},
                                      {BLT, &blt},
                                      {BNE, &bne},
                                      {BEQ, &beq},
                                      {BLTU, &bltu},
                                      {BGEU, &bgeu},
                                      {SLTI, &slti},
                                      {SLTIU, &sltiu},
                                      {SLL, &sll},
                                      {SLT, &slt},
                                      {SLTU, &sltu},
                                      {SLLI, &slli},
                                      {SRLI, &srli},
                                      {SRAI, &srai},
                                      {SRL, &srl},
                                      {SRA, &sra},
                                      {JAL, &jal},
                                      {JALR, &jalr},
                                      {LUI, &lui},
                                      {AUIPC, &auipc},
                                      {FENCE, &fence},
                                      {ECALL, &ecall},
                                      {EBREAK, &ebreak},
                                      {MUL, &mul}};
const std::map<std::string, std::string> Registers{
    {"zero", "x0"}, // 0,
    {"ra", "x1"},   // 1,
    {"sp", "x2"},   // 2,
    {"gp", "x3"},   // 3,
    {"tp", "x4"},   // 4,
    {"t0", "x5"},   // 5,
    {"t1", "x6"},   // 6,
    {"t2", "x7"},   // 7,
    {"t3", "x28"},  // 8,
    {"t4", "x29"},  // 9,
    {"t5", "x30"},  // 10,
    {"t6", "x31"},  // 11,
    {"s0", "x8"},   // 12,
    {"fp", "x8"},   // 13,
    {"s1", "x9"},   // 14,
    {"s2", "x18"},  // 15,
    {"s3", "x19"},  // 16,
    {"s4", "x20"},  // 17,
    {"s5", "x21"},  // 18,
    {"s6", "x22"},  // 19,
    {"s7", "x23"},  // 20,
    {"s8", "x24"},  // 21,
    {"s9", "x25"},  // 22,
    {"s10", "x26"}, // 23,
    {"s11", "x27"}, // 24,
    {"a0", "x10"},  // 25,
    {"a1", "x11"},  // 26,
    {"a2", "x12"},  // 27,
    {"a3", "x13"},  // 28,
    {"a4", "x14"},  // 29,
    {"a5", "x15"},  // 30,
    {"a6", "x16"},  // 31,
    {"a7", "x17"}   // 32,

};