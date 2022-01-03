#ifndef DEFS_H
#define DEFS_H
#pragma once
#include "std++.hpp"
#include "globals.hpp"

/*****Parse.cpp*****/

extern std::vector<std::vector<std::string>> StoreLabels();
extern void ModifyReg(std::string &reg);

extern std::vector<Instruction> ReadInstFile(const std::string &fileName); // reads asm instructions
extern void ReadDataFile(const std::string &fileName);

extern std::string GetInstName(const std::vector<Instruction> &instructions, int i);
extern int getInstOp(const std::string &instName);
extern void ModifyInstructions(std::vector<std::vector<std::string>> labels, std::vector<Instruction> &instructions);

extern void Three_Registers(std::string &instruction, std::string &rd, std::string &rs1, std::string &rs2);
extern void Two_Registers_OffSet(std::string &instruction, std::string &rd, std::string &rs1, int &OffSet);
extern void Register_imm(std::string &instruction, std::string &rd, std::string &imm);

/*****instructions******/
// u.cpp
extern void lui(std::string &instruction);
extern void auipc(std::string &instruction);

// j.cpp
extern void jal(std::string &instruction);
extern void jalr(std::string &instruction);

// mem.cpp
extern void lw(std::string &instruction);
extern void lb(std::string &instruction);
extern void lh(std::string &instruction);
extern void lbu(std::string &instruction);
extern void lhu(std::string &instruction);
extern void sb(std::string &instruction);
extern void sh(std::string &instruction);
extern void sw(std::string &instruction);

// B.cpp
extern void beq(std::string &instruction);
extern void bne(std::string &instruction);
extern void bltu(std::string &instruction);
extern void bgeu(std::string &instruction);
extern void blt(std::string &instruction);
extern void bge(std::string &instruction);

// I.cpp
extern void addi(std::string &instruction);
extern void xori(std::string &instruction);
extern void slti(std::string &instruction);
extern void sltiu(std::string &instruction);
extern void ori(std::string &instruction);
extern void andi(std::string &instruction);
extern void slli(std::string &instruction);
extern void srli(std::string &instruction);
extern void srai(std::string &instruction);

// R.cpp
extern void add(std::string &instruction);
extern void sub(std::string &instruction);
extern void sll(std::string &instruction);
extern void slt(std::string &instruction);
extern void sltu(std::string &instruction);
extern void _xor(std::string &instruction);
extern void srl(std::string &instruction);
extern void sra(std::string &instruction);
extern void _or(std::string &instruction);
extern void _and(std::string &instruction);

// M-extension
extern void mul(std::string &instruction);
extern void mulH(std::string &instruction);
extern void mulHU(std::string &instruction);
extern void mulHSU(std::string &instruction);
extern void div(std::string &instruction);
extern void divu(std::string &instruction);
extern void rem(std::string &instruction);
extern void remu(std::string &instruction);

// fence_sys.cpp
extern void fence(std::string &instruction);
extern void ecall(std::string &instruction);
extern void ebreak(std::string &instruction);

// utils.cpp
extern bool isNumber(std::string line);
extern int binary_to_dec(std::string input);
extern std::string dec_to_binary(int number);
extern int get_index(const std::string &reg);
extern void throw_err(const std::string &err);
extern std::string toupper(const std::string &str);
extern std::string tolower(const std::string &str);
extern void print_all_bases(int num, std::ostream &outs);
extern void print_regfile(std::ostream &outs);
extern void print_data_memory(std::ostream &outs);
extern void print_inst_memory(std::ostream &outs);

// logic.cpp
extern void initialize();
extern void simulate(std::ostream &outs);
#endif