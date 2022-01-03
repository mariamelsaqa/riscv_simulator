#include "defs.h"
#include "std++.hpp"
#include "globals.hpp"
using namespace std;

void DecideType(vector<Instruction> &instructions)
{

  std::string inst = GetInstName(instructions, ((PC - starting_address) / 4));
  std::string input = instructions[((PC - starting_address) / 4)].input;

  if (inst == "addi")
    addi(input);

  if (inst == "lbu")

    lbu(input);

  if (inst == "lhu")

    lhu(input);

  if (inst == "sb")

    sb(input);

  if (inst == "sh")

    sh(input);

  if (inst == "sw")

    sw(input);

  if (inst == "slti")

    slti(input);

  if (inst == "sltiu")

    sltiu(input);

  if (inst == "xori")

    xori(input);

  if (inst == "ori")

    ori(input);

  if (inst == "andi")

    andi(input);

  if (inst == "slli")

    slli(input);

  if (inst == "srli")

    srli(input);

  if (inst == "srai")

    srai(input);

  if (inst == "add")

    add(input);

  if (inst == "sub")

    sub(input);

  if (inst == "sll")

    sll(input);

  if (inst == "slt")

    slt(input);

  if (inst == "srai")

    srai(input);

  if (inst == "sltu")

    sltu(input);

  if (inst == "xor")

    _xor(input);

  if (inst == "srl")
    srl(input);

  if (inst == "sra")
    sra(input);

  if (inst == "or")
    _or(input);

  if (inst == "and")

    _and(input);

  if (inst == "bge")

    bge(input);

  if (inst == "blt")

    blt(input);

  if (inst == "lw")

    lw(input);

  if (inst == "lh")

    lh(input);

  if (inst == "lb")

    lb(input);

  if (inst == "bgeu")

    bgeu(input);

  if (inst == "bltu")

    bltu(input);

  if (inst == "bne")

    bne(input);

  if (inst == "beq")

    beq(input);

  if (inst == "jalr")

    jalr(input);

  if (inst == "jal")

    jal(input);

  if (inst == "auipc")

    auipc(input);

  if (inst == "lui")

    lui(input);

  if (inst == "fence")
  {
    cout << "FENCE instruction stops the program" << endl;
    exit(EXIT_SUCCESS);
  }
  if (inst == "ecall")
  {
    cout << "ECALL instruction stops the program" << endl;
    exit(EXIT_SUCCESS);
  }
  if (inst == "ebreak")
  {
    cout << "EBREAK instruction stops the program" << endl;
    exit(EXIT_SUCCESS);
  }
  if (inst == "mul")
    mul(input);

  if (inst == "mulh")
    mulH(input);

  if (inst == "mulhu")
    mulHU(input);

  if (inst == "mulhsu")
    mulHSU(input);

  if (inst == "div")
    div(input);

  if (inst == "divu")
    divu(input);

  if (inst == "rem")
    rem(input);

  if (inst == "remu")
    remu(input);
}

void callFunctions()
{
  auto instructions = ReadInstFile(path);
  ReadDataFile(path2);
  auto labels = StoreLabels();
  ModifyInstructions(labels, instructions);

  cout << "Original Code: " << endl;
  for (int i = 0; i < instructions.size(); i++)
  {
    cout << instructions[i].input << endl;
  }
  cout << endl;

  if (instructions[instructions.size() - 1].input.size() < 2)
  {
    MAX_PC = starting_address + (instructions.size() * 4) - 8;
  }
  else
  {
    MAX_PC = starting_address + (instructions.size() * 4) - 4;
  }

  // cout<<"MAX_PC"<<MAX_PC<<endl;
  while (PC <= MAX_PC)
  {
    cout << "PC: " << endl;
    cout << "Dec: " << dec << PC << "  "
         << "Hex: " << hex << PC << "  "
         << "Bin: " << dec_to_binary(PC) << endl;
    DecideType(instructions);

    cout << "Reg File contents after instruction " << ((PC - starting_address) / 4) << endl;
    regFile[0] = 0;
    for (int i = 0; i < 32; i++)
    {
      cout << "x" << dec << i << "---> "
           << "Dec: " << dec << regFile[i] << "  "
           << "Hex: " << hex << regFile[i] << "  "
           << "Bin: " << dec_to_binary(regFile[i]) << endl;
    }
    cout << endl;

    cout << "Memory Content:" << endl;
    for (int i = 0; i < stored_adresses.size(); i++)
    {
      cout << "Dec: ";
      cout << dec << stored_adresses[i] << "," << dec << stored_values[i] << "//";

      cout << "Hex: ";
      cout << hex << stored_adresses[i] << "," << hex << stored_values[i] << "//";

      cout << "Bin: ";
      cout << dec_to_binary(stored_adresses[i]) << "," << dec_to_binary(stored_values[i]) << endl;
    }
    cout << "----------------------------" << endl;
    cout << endl;
  }
  cout << endl;

  cout << "Basic Code: " << endl;
  for (int i = 0; i < instructions.size(); i++)
  {
    cout << instructions[i].input << endl;
  }
  cout << endl;
}

int main()
{
  cout << "What is the program's starting Address?" << endl;
  cin >> starting_address;
  PC = starting_address;
  callFunctions();
  return 0;
}
