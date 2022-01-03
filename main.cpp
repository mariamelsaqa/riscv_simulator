#include "common.hpp"
#include "instructions.hpp"
#include "utils.hpp"
#include "registers.hpp"
using namespace std;

string path = "Test.txt";
string path2 = "Data.txt";

array<int, 32> regFile;
unsigned int PC;
int MAX_PC;
int starting_address;
vector<int> stored_adresses;
vector<int> stored_values;

struct Instruction
{
  string input;
};

void ModifyReg(string &reg)
{
  auto found = Registers.find(reg);
  if (found != Registers.end())
    reg = found->second;
}

vector<Instruction> ReadFile(const string &fileName) // reads asm instructions
{
  vector<Instruction> instructions;
  ifstream file(fileName);
  if (!file.is_open())
  {
    cout
        << "Open a good file" << endl; // haha...
    exit(-1);
  }
  else
  {
    while (!file.eof())
    {
      string input;
      getline(file, input);
      instructions.push_back({input});
    }
    return instructions;
  }
}

vector<vector<string>> StoreLabels()
{
  auto instructions = ReadFile(path);
  int numberOfLines = 0;
  vector<vector<string>> labels;

  for (int i = 0; i < instructions.size(); i++)
  {
    int pos = instructions[i].input.find(":");
    vector<string> store;
    if (pos > 0)
    {
      string sub = instructions[i].input.substr(0, pos);
      store.push_back(sub);
      store.push_back(to_string(numberOfLines));
      labels.push_back(store);
    }
    numberOfLines += 4;
  }
  return labels;
}

string GetInstruction(vector<Instruction> instructions, int i)
{
  int index;
  string Instruction;
  int pos = instructions[i].input.find(":");
  // index= (pos>0)?pos+1:index;
  if (pos > 0)
  {
    index = pos + 1;
  }
  else
  {
    index = 0;
  }
  int FindSpace = instructions[i].input.find(" ");
  if (FindSpace > 0)
  {
    if (index == 0)
    {
      Instruction = instructions[i].input.substr(index, FindSpace);
    }
    else
    {
      Instruction = instructions[i].input.substr(index, index - 2);
    }
  }
  return Instruction;
}

void ReadDataFile(const string &fileName)
{
  ifstream file(fileName);

  if (!file.is_open())
  {
    cout << "Open a good file" << endl;
    exit(-1);
  }
  else
  {
    while (!file.eof())
    {
      int input1;
      int input2;
      file >> input1 >> input2;
      stored_adresses.push_back(input1);

      stored_values.push_back(input2);
    }
  }
}

void ModifyInstructions(vector<vector<string>> labels, vector<Instruction> &instructions)
{
  string Instruction;
  int numberofLines = 0;
  int Difference;
  int index;

  for (int i = 0; i < instructions.size(); i++)
  {
    Instruction = GetInstruction(instructions, i);
    if (Instruction == instructionsHeadings[17] || Instruction == instructionsHeadings[18] || Instruction == instructionsHeadings[19] || Instruction == instructionsHeadings[20] || Instruction == instructionsHeadings[21] || Instruction == instructionsHeadings[22])
    {
      string LabelFound;
      int FindFirstComma = instructions[i].input.find(",");
      int FindSecondComma;
      // cout<<FindFirstComma<<endl;
      if (FindFirstComma > 0)
      {
        string sub = instructions[i].input.substr(FindFirstComma + 1, '\n');
        FindSecondComma = sub.find(",");
        LabelFound = sub.substr(FindSecondComma + 1, '\n');
      }
      for (int j = 0; j < labels.size(); j++)
      {
        if (LabelFound == labels[j][0])
        {
          Difference = stoi(labels[j][1]) - numberofLines;
        }
      }
      int FindSecondCommainALL = FindFirstComma + 2 + FindSecondComma;
      instructions[i].input.replace(FindSecondCommainALL, instructions[i].input.size() - FindSecondCommainALL, to_string(Difference));
    }
    if (Instruction == instructionsHeadings[33])
    {
      string LabelFound;
      int FindFirstComma = instructions[i].input.find(",");
      if (FindFirstComma > 0)
      {
        LabelFound = instructions[i].input.substr(FindFirstComma + 1, '\n');
        // cout<<LabelFound<<endl;
      }
      for (int j = 0; j < labels.size(); j++)
      {
        if (LabelFound == labels[j][0])
        {
          Difference = stoi(labels[j][1]) - numberofLines;
        }
      }
      instructions[i].input.replace(FindFirstComma + 1, instructions[i].input.size() - FindFirstComma + 1, to_string(Difference));
    }
    int FindLabel = instructions[i].input.find(":");
    instructions[i].input = instructions[i].input.substr(FindLabel + 1, instructions[i].input.size());
    if (instructions[i].input.size() < 2)
    {
      instructions.erase(instructions.begin() + i);
    }
    numberofLines += 4;
  }
}

void Three_Registers(string &instruction, string &rd, string &rs1, string &rs2)
{
  int FindSpace = instruction.find(" ");
  if (FindSpace > 0)
  {
    string sub1 = instruction.substr(FindSpace + 1, '\n');
    int FindFirstComma = sub1.find(",");
    rd = instruction.substr(FindSpace + 1, FindFirstComma);
    if (rd[0] != 'x')
    {
      ModifyReg(rd);

      instruction.replace(FindSpace + 1, FindFirstComma, rd);
    }
    // cout<<rd<<endl;
    string sub2 = sub1.substr(FindFirstComma + 1, '\n');
    int FindSecondComma = sub2.find(",");
    rs1 = sub1.substr(FindFirstComma + 1, FindSecondComma);
    // cout<<"rs1 "<<rs1<<endl;
    if (rs1[0] != 'x')
    {
      // cout<<"ay7aga??"<<endl;
      ModifyReg(rs1);
      if (rd.size() == 2)
      {
        instruction.replace(FindSpace + FindFirstComma + 2, FindSecondComma, rs1);
      }
      else if (rd.size() > 2 && rs1.size() == 2)
      {
        // cout<<"Here1 "<<instruction<<endl;
        instruction.replace(FindSpace + FindFirstComma + 4, FindSecondComma, rs1);
      }
      else if (rd.size() > 2 && rs1.size() > 2)
      {
        // cout<<"Here "<<instruction<<"size: "<<instruction.size()<<endl;
        instruction.replace(FindSpace + FindFirstComma + 3, FindSecondComma, rs1);
      }
    }
    rs2 = sub2.substr(FindSecondComma + 1, '\n');
    // cout<<"rs2 "<<rs2<<endl;
    if (isNumber(rs2) == false)
    {
      if (rs2[0] != 'x')
      {
        ModifyReg(rs2);
        if (rs1.size() == 2)
        {
          instruction.replace(FindSpace + FindFirstComma + FindSecondComma + 3, instruction.size() - FindSecondComma + 2, rs2);
        }
        else if (rs1.size() != 2 && rd.size() == 2)
        {
          instruction.replace(FindSpace + FindFirstComma + FindSecondComma + 4, instruction.size() - FindSecondComma + 2, rs2);
        }
        else
        {
          instruction.replace(FindSpace + FindFirstComma + FindSecondComma + 5, instruction.size() - FindSecondComma + 2, rs2);
        }
      }
    }
    // cout<<instruction<<endl;
    // cout<<rs2<<endl;
  }
}

void Two_Registers_OffSet(string &instruction, string &rd, string &rs1, int &OffSet)
{
  int FindSpace = instruction.find(" ");
  if (FindSpace > 0)
  {
    string sub1 = instruction.substr(FindSpace + 1, '\n');
    int FindFirstComma = sub1.find(",");
    rd = instruction.substr(FindSpace + 1, FindFirstComma);
    if (rd[0] != 'x')
    {
      ModifyReg(rd);
      instruction.replace(FindSpace + 1, FindFirstComma, rd);
    }
    // cout<<rd<<endl;
    string sub2 = sub1.substr(FindFirstComma + 1, '\n');
    int FindFirstBracket = sub2.find("(");
    string OffSet_string = sub1.substr(FindFirstComma + 1, FindFirstBracket);
    OffSet = stoi(OffSet_string);
    // cout<<OffSet<<endl;
    string sub3 = sub2.substr(FindFirstBracket + 1, '\n');
    int FindSecondBracket = sub3.find(")");
    rs1 = sub2.substr(FindFirstBracket + 1, FindSecondBracket);
    if (rs1[0] != 'x')
    {
      ModifyReg(rs1);
      if (rd.size() == 2)
      {
        instruction.replace(FindSpace + FindFirstComma + FindFirstBracket + 3, FindSecondBracket, rs1);
      }
      else
      {
        instruction.replace(FindSpace + FindFirstComma + FindFirstBracket + 4, FindSecondBracket, rs1);
      }
    }
    // cout<<rs1<<endl;
  }
}

void Register_imm(string &instruction, string &rd, string &imm)
{
  int FindSpace = instruction.find(" ");
  if (FindSpace > 0)
  {
    string sub1 = instruction.substr(FindSpace + 1, '\n');
    int FindFirstComma = sub1.find(",");
    rd = instruction.substr(FindSpace + 1, FindFirstComma);
    if (rd[0] != 'x')
    {
      ModifyReg(rd);
      instruction.replace(FindSpace + 1, FindFirstComma, rd);
    }
    // cout<<"rd " <<rd<<endl;
    imm = sub1.substr(FindFirstComma + 1, '\n');
    // cout<<"rs1 "<<rs1<<endl;
  }
}

// utils

void lui(string &instruction)
{
  string rd, imm_s;
  Register_imm(instruction, rd, imm_s);
  int imm = stoi(imm_s);
  int temp = imm * 4096; // shift 12 bits
  regFile[get_index(rd)] = regFile[get_index(rd)] + temp;
  PC += 4;
}

void auipc(string &instruction)
{
  string rd, imm_s;
  Register_imm(instruction, rd, imm_s);
  int imm = stoi(imm_s);
  regFile[get_index(rd)] = (imm * 4096) + PC; // shift 12 bits
  PC += 4;
}

void jal(string &instruction)
{
  string rd, imm_s;
  Register_imm(instruction, rd, imm_s);
  int imm = stoi(imm_s);
  regFile[get_index(rd)] = PC + 4;
  PC += imm;
}

void jalr(string &instruction)
{
  string rd, rs1;
  int offset;
  Two_Registers_OffSet(instruction, rd, rs1, offset);
  regFile[get_index(rd)] = PC + 4;
  PC = regFile[get_index(rs1)] + offset;
}

void lb(string &instruction)
{
  string rd, rs1;
  int offset;
  string final_bin = "";
  int number;

  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;

  for (int i = 0; i < stored_adresses.size(); i++)
    if (stored_adresses[i] == address)
      number = stored_values[i];

  string binary = dec_to_binary(number);
  while (binary.size() < 32)
  {
    binary = '0' + binary;
  }
  for (int i = 23; i < 32; i++)
    final_bin = final_bin + binary[i];
  regFile[get_index(rd)] = binary_to_dec(final_bin);
  PC += 4;
}

void lh(string &instruction)
{
  string rd, rs1;
  int offset;
  string final_bin = "";
  int number;

  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;
  for (int i = 0; i < stored_adresses.size(); i++)
    if (stored_adresses[i] == address)
      number = stored_values[i];
  string binary = dec_to_binary(number);
  while (binary.size() < 32)
  {
    binary = '0' + binary;
  }
  for (int i = 15; i < 32; i++)
    final_bin = final_bin + binary[i];
  regFile[get_index(rd)] = binary_to_dec(final_bin);

  PC += 4;
}

void lbu(string &instruction)
{
  string rd, rs1;
  int offset;
  string final_bin = "";
  int number;

  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;

  for (int i = 0; i < stored_adresses.size(); i++)
    if (stored_adresses[i] == address)
      number = stored_values[i];

  int temp = number << 24 >> 24;
  // string binary = dec_to_binary(number);
  // while(binary.size() < 32)
  // {
  //   binary = '0' + binary;
  // }
  // for(int i = 23; i < 32; i++)
  //   final_bin = final_bin + binary[i];
  regFile[get_index(rd)] = temp;

  PC += 4;
}

void lhu(string &instruction)
{
  string rd, rs1;
  int offset;
  string final_bin = "";
  int number;

  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;

  for (int i = 0; i < stored_adresses.size(); i++)
    if (stored_adresses[i] == address)
      number = stored_values[i];

  int temp = number << 16 >> 16;
  // string binary = dec_to_binary(number);
  // while(binary.size() < 32)
  // {
  //   binary = '0' + binary;
  // }
  // for(int i = 23; i < 32; i++)
  //   final_bin = final_bin + binary[i];
  regFile[get_index(rd)] = temp;

  PC += 4;
}

void beq(string &instruction)
{
  string rs1, rs2, imm;
  Three_Registers(instruction, rs1, rs2, imm);
  int immediate = stoi(imm);

  if (regFile[get_index(rs1)] == regFile[get_index(rs2)])
  {
    PC += immediate;
  }
  else
  {
    PC += 4;
  }
}

void bne(string &instruction)
{
  string rs1, rs2, imm;
  Three_Registers(instruction, rs1, rs2, imm);
  int immediate = stoi(imm);

  if (regFile[get_index(rs1)] != regFile[get_index(rs2)])
  {
    PC += immediate;
  }
  else
  {
    PC += 4;
  }
}

void bltu(string &instruction)
{
  string rs1, rs2, imm;
  Three_Registers(instruction, rs1, rs2, imm);
  int immediate = stoi(imm);

  if ((unsigned int)regFile[get_index(rs1)] < (unsigned int)regFile[get_index(rs2)])
  {
    PC += immediate;
  }
  else
  {
    PC += 4;
  }
}

void bgeu(string &instruction)
{
  string rs1, rs2, imm;
  Three_Registers(instruction, rs1, rs2, imm);
  int immediate = stoi(imm);

  if ((unsigned int)regFile[get_index(rs1)] >= (unsigned int)regFile[get_index(rs2)])
  {
    PC += immediate;
  }
  else
  {
    PC += 4;
  }
}

void lw(string &instruction)
{
  string rd, rs1;
  int offset;
  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;
  for (int i = 0; i < stored_adresses.size(); i++)
  {
    if (stored_adresses[i] == address)
    {
      regFile[get_index(rd)] = stored_values[i];
    }
  }
  PC = PC + 4;
}

void blt(string &instruction)
{
  string rs2, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rs1, rs2, imm_s);
  imm = stoi(imm_s);

  if (regFile[get_index(rs1)] < regFile[get_index(rs2)])
    PC += imm;
  else
    PC += 4;
}

void bge(string &instruction)
{
  string rs1, rs2, imm_s;
  int imm;
  Three_Registers(instruction, rs1, rs2, imm_s);
  imm = stoi(imm_s);

  if (regFile[get_index(rs1)] >= regFile[get_index(rs2)])
    PC += imm;
  else
    PC += 4;
}

void addi(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);
  regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
  PC += 4;
}

void xori(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
  PC += 4;
}

void sb(string &instruction)
{
  bool flag = false;
  string rd, rs1;
  int offset;
  string final_bin = "";
  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;
  string binary = dec_to_binary(regFile[get_index(rd)]);
  while (binary.size() < 32)
  {
    binary = '0' + binary;
  }
  for (int i = 23; i < 32; i++)
  {
    final_bin = final_bin + binary[i];
  }
  for (int i = 0; i < stored_adresses.size(); i++)
  {
    if (stored_adresses[i] == address)
    {
      stored_values[i] = binary_to_dec(final_bin);
      flag = true;
      break;
    }
  }
  if (!flag)
  {
    stored_adresses.push_back(address);
    stored_values.push_back(binary_to_dec(final_bin));
  }
  PC += 4;
}

void sh(string &instruction)
{
  bool flag = false;
  string rd, rs1;
  int offset;
  string final_bin = "";

  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;

  string binary = dec_to_binary(regFile[get_index(rd)]);
  while (binary.size() < 32)
  {
    binary = '0' + binary;
  }
  for (int i = 15; i < 32; i++)
  {
    final_bin = final_bin + binary[i];
  }
  for (int i = 0; i < stored_adresses.size(); i++)
  {
    if (stored_adresses[i] == address)
    {
      stored_values[i] = binary_to_dec(final_bin);
      flag = true;
      break;
    }
  }
  if (!flag)
  {
    stored_adresses.push_back(address);
    stored_values.push_back(binary_to_dec(final_bin));
  }
  PC += 4;
}

void sw(string &instruction)
{
  bool flag = false;
  string rd, rs1;
  int offset;
  Two_Registers_OffSet(instruction, rd, rs1, offset);
  int address = regFile[get_index(rs1)] + offset;
  for (int i = 0; i < stored_adresses.size(); i++)
  {
    if (stored_adresses[i] == address)
    {
      stored_values[i] = regFile[get_index(rd)];
      flag = true;
      break;
    }
  }
  if (!flag)
  {
    stored_adresses.push_back(address);
    stored_values.push_back(regFile[get_index(rd)]);
  }
  PC = PC + 4;
}

void slti(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  if (regFile[get_index(rs1)] < imm)
    regFile[get_index(rd)] = 1;
  else
    regFile[get_index(rd)] = 0;
  PC += 4;
}

void sltiu(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  if (regFile[get_index(rs1)] < imm)
    regFile[get_index(rd)] = 1;
  else
    regFile[get_index(rd)] = 0;
  PC += 4;
}

void ori(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  regFile[get_index(rd)] = regFile[get_index(rs1)] | imm;
  PC += 4;
}

void andi(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  regFile[get_index(rd)] = regFile[get_index(rs1)] & imm;
  PC += 4;
}

void slli(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  regFile[get_index(rd)] = regFile[get_index(rs1)] << imm;
  PC += 4;
}

void srli(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  regFile[get_index(rd)] = regFile[get_index(rs1)] >> imm;
  PC += 4;
}

void srai(string &instruction)
{
  string rd, rs1, imm_s;
  int imm;
  Three_Registers(instruction, rd, rs1, imm_s);
  imm = stoi(imm_s);

  regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)imm;
  PC += 4;
}

void add(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] + regFile[get_index(rs2)];
  PC += 4;
}

void sub(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] - regFile[get_index(rs2)];
  PC += 4;
}

void sll(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] << regFile[get_index(rs2)];
  PC += 4;
}

void slt(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  if (regFile[get_index(rs1)] < regFile[get_index(rs2)])
    regFile[get_index(rd)] = 1;
  else
    regFile[get_index(rd)] = 0;
  PC += 4;
}

void sltu(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] << (unsigned int)regFile[get_index(rs2)];
  PC += 4;
}

void x_or(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] ^ regFile[get_index(rs2)];
  PC += 4;
}

void srl(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] >> regFile[get_index(rs2)];
  PC += 4;
}

void sra(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)regFile[get_index(rs2)];
  PC += 4;
}

void or_instruction(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] | regFile[get_index(rs2)];
  PC += 4;
}

void and_instruction(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] & regFile[get_index(rs2)];
  PC += 4;
}

void mul(string &instruction)
{
  string rd, rs1, rs2;
  cout << "WE ARE HERE" << endl;
  Three_Registers(instruction, rd, rs1, rs2);

  long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
  regFile[get_index(rd)] = x & (0x00000000FFFFFFFF);

  PC += 4;
}

void mulH(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
  regFile[get_index(rd)] = x >> 32;

  PC += 4;
}

void mulHU(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  unsigned long int x = (unsigned long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
  regFile[get_index(rd)] = x >> 32;

  PC += 4;
}

void mulHSU(string &instruction)
{
  string rd, rs1, rs2;
  Three_Registers(instruction, rd, rs1, rs2);

  unsigned long int x = (signed long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
  regFile[get_index(rd)] = x >> 32;

  PC += 4;
}

void div(string &instruction)
{
  string rd, rs1, rs2;
  int result;
  Three_Registers(instruction, rd, rs1, rs2);

  if (regFile[get_index(rs2)] == 0)
  { // dividing by zero
    result = -1;
  }
  else if (regFile[get_index(rs1)] == 0x80000000 && regFile[get_index(rs2)] == -1)
  {                      // overflow
    result = 0x80000000; //-2^XLEN-1
  }
  else
  {
    result = regFile[get_index(rs1)] / regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC += 4;
}

void divu(string &instruction)
{
  string rd, rs1, rs2;
  unsigned int result;
  Three_Registers(instruction, rd, rs1, rs2);

  if (regFile[get_index(rs2)] == 0)
  {                      // dividing by zero
    result = 0xFFFFFFFF; //(2^XLen)-1
  }
  else
  {
    result = (unsigned int)regFile[get_index(rs1)] / (unsigned int)regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC += 4;
}

void rem(string &instruction)
{
  string rd, rs1, rs2;
  int result;
  Three_Registers(instruction, rd, rs1, rs2);

  if (regFile[get_index(rs2)] == 0)
  {
    result = regFile[get_index(rs1)];
  }
  else if (regFile[get_index(rs1)] == 0x80000000 && regFile[get_index(rs2)] == -1)
  {
    result = 0;
  }
  else
  {
    result = regFile[get_index(rs1)] % regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC += 4;
}

void remu(string &instruction)
{
  string rd, rs1, rs2;
  unsigned int result;
  Three_Registers(instruction, rd, rs1, rs2);

  if (regFile[get_index(rs2)] == 0)
  {
    result = regFile[get_index(rs1)];
  }
  else
  {
    result = (unsigned int)regFile[get_index(rs1)] % (unsigned int)regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC += 4;
}

void DecideType(vector<Instruction> &instructions)
{

  std::string inst = GetInstruction(instructions, ((PC - starting_address) / 4));
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

    x_or(input);

  if (inst == "srl")
    srl(input);

  if (inst == "sra")
    sra(input);

  if (inst == "or")
    or_instruction(input);

  if (inst == "and")

    and_instruction(input);

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
  auto instructions = ReadFile(path);
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
