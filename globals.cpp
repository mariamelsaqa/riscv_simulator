#include "globals.hpp"
#include "ops.hpp"
#include "defs.h"

std::string path = "inst.txt";
std::string path2 = "data.txt";

std::array<int, 32> regFile;
unsigned int PC = 0;
int MAX_PC;
int starting_address = 0;
std::vector<int> stored_adresses;
std::vector<int> stored_values;

const std::string instNames[] = {
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

extern const std::map<std::string, int> instOps{
    {"add", ADD_OP},
    {"addi", ADDI_OP},
    {"sub", SUB_OP},
    {"xor", XOR_OP},
    {"or", OR_OP},
    {"xori", XORI_OP},
    {"ori", ORI_OP},
    {"andi", ANDI_OP},
    {"and", AND_OP},
    {"lb", LB_OP},
    {"lw", LW_OP},
    {"lh", LH_OP},
    {"lbu", LBU_OP},
    {"lhu", LHU_OP},
    {"sb", SB_OP},
    {"sh", SH_OP},
    {"sw", SW_OP},
    {"bge", BGE_OP},
    {"blt", BLT_OP},
    {"bne", BNE_OP},
    {"beq", BEQ_OP},
    {"bltu", BLTU_OP},
    {"bgeu", BGEU_OP},
    {"slti", SLTI_OP},
    {"sltiu", SLTIU_OP},
    {"sll", SLL_OP},
    {"slt", SLT_OP},
    {"sltu", SLTU_OP},
    {"slli", SLLI_OP},
    {"srli", SRLI_OP},
    {"srai", SRAI_OP},
    {"srl", SRL_OP},
    {"sra", SRA_OP},
    {"jal", JAL_OP},
    {"jalr", JALR_OP},
    {"lui", LUI_OP},
    {"auipc", AUIPC_OP},
    {"fence", FENCE_OP},
    {"ecall", ECALL_OP},
    {"ebreak", EBREAK_OP},
    {"mul", MUL_OP},
};

std::vector<Instruction> inst_mem;
const std::map<int, instFunc_t> instMap{{ADD_OP, &add},
                                        {ADDI_OP, &addi},
                                        {SUB_OP, &sub},
                                        {XOR_OP, &_xor},
                                        {OR_OP, &_or},
                                        {XORI_OP, &xori},
                                        {ORI_OP, &ori},
                                        {ANDI_OP, &andi},
                                        {AND_OP, &_and},
                                        {LB_OP, &lb},
                                        {LW_OP, &lw},
                                        {LH_OP, &lh},
                                        {LBU_OP, &lbu},
                                        {LHU_OP, &lhu},
                                        {SB_OP, &sb},
                                        {SH_OP, &sh},
                                        {SW_OP, &sw},
                                        {BGE_OP, &bge},
                                        {BLT_OP, &blt},
                                        {BNE_OP, &bne},
                                        {BEQ_OP, &beq},
                                        {BLTU_OP, &bltu},
                                        {BGEU_OP, &bgeu},
                                        {SLTI_OP, &slti},
                                        {SLTIU_OP, &sltiu},
                                        {SLL_OP, &sll},
                                        {SLT_OP, &slt},
                                        {SLTU_OP, &sltu},
                                        {SLLI_OP, &slli},
                                        {SRLI_OP, &srli},
                                        {SRAI_OP, &srai},
                                        {SRL_OP, &srl},
                                        {SRA_OP, &sra},
                                        {JAL_OP, &jal},
                                        {JALR_OP, &jalr},
                                        {LUI_OP, &lui},
                                        {AUIPC_OP, &auipc},
                                        {FENCE_OP, &fence},
                                        {ECALL_OP, &ecall},
                                        {EBREAK_OP, &ebreak},
                                        {MUL_OP, &mul}};
const std::map<std::string, std::string> regNames{
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