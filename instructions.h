#pragma once
#include "common.h"
using namespace std;

#define ADD 0
#define ADDI 1
#define SUB 2
#define XOR 3
#define OR 4
#define XORI 5
#define ORI 6
#define ANDI 7
#define AND 8
#define LB 9
#define LW 10
#define LH 11
#define LBU 12
#define LHU 13
#define SB 14
#define SH 15
#define SW 16
#define BGE 17
#define BLT 18
#define BNE 19
#define BEQ 20
#define BLTU 21
#define BGEU 22
#define SLTI 23
#define SLTIU 24
#define SLL 25
#define SLT 26
#define SLTU 27
#define SLLI 28
#define SRLI 29
#define SRAI 30
#define SRL 31
#define SRA 32
#define JAL 33
#define JALR 34
#define LUI 35
#define AUIPC 36
#define FENCE 37
#define ECALL 38
#define EBREAK 39
#define MUL 40

//move to different header
string(instructionsHeadings[]) = {
    "add",    //0
    "addi",   //1
    "sub",    //2
    "xor",    //3
    "or",     //4
    "xori",   //5
    "ori",    //6
    "andi",   //7
    "and",    //8
    "lb",     //9
    "lw",     //10
    "lh",     //11
    "lbu",    //12
    "lhu",    //13
    "sb",     //14
    "sh",     //15
    "sw",     //16
    "bge",    //17
    "blt",    //18
    "bne",    //19
    "beq",    //20
    "bltu",   //21
    "bgeu",   //22
    "slti",   //23
    "sltiu",  //24
    "sll",    //25
    "slt",    //26
    "sltu",   //27
    "slli",   //28
    "srli",   //29
    "srai",   //30
    "srl",    //31
    "sra",    //32
    "jal",    //33
    "jalr",   //34
    "lui",    //35
    "auipc",  //36
    "fence",  //37
    "ecall",  //38
    "ebreak", //39
    "mul",    //40
};

//u-type
extern void lui(string &instruction);
extern void auipc(string &instruction);

//j-type
extern void jal(string &instruction);
extern void jalr(string &instruction);

//memory
extern void lw(string &instruction);
extern void lb(string &instruction);
extern void lh(string &instruction);
extern void lbu(string &instruction);
extern void lhu(string &instruction);
extern void sb(string &instruction);
extern void sh(string &instruction);
extern void sw(string &instruction);

//B-type
extern void beq(string &instruction);
extern void bne(string &instruction);
extern void bltu(string &instruction);
extern void bgeu(string &instruction);
extern void blt(string &instruction);
extern void bge(string &instruction);

//I-type
extern void addi(string &instruction);
extern void xori(string &instruction);
extern void slti(string &instruction);
extern void sltiu(string &instruction);
extern void ori(string &instruction);
extern void andi(string &instruction);
extern void slli(string &instruction);
extern void srli(string &instruction);
extern void srai(string &instruction);

//R-type
extern void add(string &instruction);
extern void sub(string &instruction);
extern void sll(string &instruction);
extern void slt(string &instruction);
extern void sltu(string &instruction);
extern void x_or(string &instruction);
extern void srl(string &instruction);
extern void sra(string &instruction);
extern void or_instruction(string &instruction);
extern void and_instruction(string &instruction);
//M-extension
extern void mul(string &instruction);
extern void mulH(string &instruction);
extern void mulHU(string &instruction);
extern void mulHSU(string &instruction);
extern void div(string &instruction);
extern void divu(string &instruction);
extern void rem(string &instruction);
extern void remu(string &instruction);