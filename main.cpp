#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdint.h>
using namespace std;

string path = "/Users/mariamelsaqa/Desktop/Assembly/Project1Assembly/Project1Assembly/Test.txt";
string path2 = "/Users/mariamelsaqa/Desktop/Assembly/Project1Assembly/Project1Assembly/Data.txt";

array<int, 32> regFile;
unsigned int PC;
int MAX_PC;
int starting_address;
vector<int>stored_adresses;
vector<int>stored_values;

struct Instruction
{
    string input;
};

string instructionsHeadings[] = {
    "add", //0
    "addi", //1
    "sub", //2
    "xor", //3
    "or", //4
    "xori",  //5
    "ori",  //6
    "andi", //7
    "and",  //8
    "lb",  //9
    "lw",  //10
    "lh", //11
    "lbu",  //12
    "lhu",  //13
    "sb",  //14
    "sh",  //15
    "sw",  //16
    "bge", //17
    "blt",  //18
    "bne",  //19
    "beq",  //20
    "bltu", //21
    "bgeu",  //22
    "slti",  //23
    "sltiu",  //24
    "sll", //25
    "slt", //26
    "sltu", //27
    "slli", //28
    "srli", //29
    "srai", //30
    "srl", //31
    "sra", //32
    "jal", //33
    "jalr",  //34
    "lui",  //35
    "auipc",  //36
    "fence",  //37
    "ecall",  //38
    "ebreak",  //39
    "mul", //40
};

string Registers[]{
  "zero", //0, x0
  "ra", //1, x1
  "sp", //2, x2
  "gp", //3, x3
  "tp", //4, x4
  "t0", //5, x5
  "t1", //6, x6
  "t2", //7, x7
  "t3", //8, x28
  "t4", //9, x29
  "t5", //10, x30
  "t6", //11, x31
  "s0", //12, x8
  "fp", //13, x8
  "s1", //14, x9
  "s2", //15, x18
  "s3", //16, x19
  "s4", //17, x20
  "s5", //18, x21
  "s6", //19, x22
  "s7", //20, x23
  "s8", //21, x24
  "s9", //22, x25
  "s10", //23, x26
  "s11", //24, x27
  "a0", //25, x10
  "a1", //26, x11
  "a2", //27, x12
  "a3", //28, x13
  "a4", //29, x14
  "a5", //30, x15
  "a6", //31, x16
  "a7", //32, x17

};

void ModifyReg(string &reg){
    if (reg == Registers[0]) {
        reg = "x0";
    }
    else if (reg == Registers[1]){
        reg = "x1";
    }
    else if (reg == Registers[2]){
        reg = "x2";
    }
    else if (reg == Registers[3]){
        reg = "x3";
    }
    else if (reg == Registers[4]){
        reg = "x4";
    }
    else if (reg == Registers[5]){
        reg = "x5";
    }
    else if (reg == Registers[6]){
        reg = "x6";
    }
    else if (reg == Registers[7]){
        reg = "x7";
    }
    else if (reg == Registers[8]){
        reg = "x28";
    }
    else if (reg == Registers[9]){
        reg = "x29";
    }
    else if (reg == Registers[10]){
        reg = "x30";
    }
    else if (reg == Registers[11]){
        reg = "x31";
    }
    else if (reg == Registers[12]){
        reg = "x8";
    }
    else if (reg == Registers[13]){
        reg = "x8";
    }
    else if (reg == Registers[14]){
        reg = "x9";
    }
    else if (reg == Registers[15]){
        reg = "x18";
    }
    else if (reg == Registers[16]){
        reg = "x19";
    }
    else if (reg == Registers[17]){
        reg = "x20";
    }
    else if (reg == Registers[18]){
        reg = "x21";
    }
    else if (reg == Registers[19]){
        reg = "x22";
    }
    else if (reg == Registers[20]){
        reg = "x23";
    }
    else if (reg == Registers[21]){
        reg = "x24";
    }
    else if (reg == Registers[22]){
        reg = "x25";
    }
    else if (reg == Registers[23]){
        reg = "x26";
    }
    else if (reg == Registers[24]){
        reg = "x27";
    }
    else if (reg == Registers[25]){
        reg = "x10";
    }
    else if (reg == Registers[26]){
        reg = "x11";
    }
    else if (reg == Registers[27]){
        reg = "x12";
    }
    else if (reg == Registers[28]){
        reg = "x13";
    }
    else if (reg == Registers[29]){
        reg = "x14";
    }
    else if (reg == Registers[30]){
        reg = "x15";
    }
    else if (reg == Registers[31]){
        reg = "x16";
    }
    else if (reg == Registers[32]){
        reg = "x17";
    }
}

bool isNumber(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
 }

vector<Instruction> ReadFile(const string& fileName)
{
    vector<Instruction> instructions;
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
            string input;
            getline(file, input);
            instructions.push_back({ input });
        }
        return instructions;
    }
}

vector<vector<string>> StoreLabels() {
    auto instructions = ReadFile(path);
    int numberOfLines = 0;
    vector<vector<string>> labels;
    
    for (int i = 0; i < instructions.size(); i++)
    {
        int pos = instructions[i].input.find(":");
        vector<string> store;
        if (pos > 0)
        {
            string sub = instructions[i].input.substr(0,pos);
            store.push_back(sub);
            store.push_back(to_string(numberOfLines));
            labels.push_back(store);
        }
        numberOfLines += 4;
    }
    return labels;
}

string GetInstruction(vector<Instruction> instructions, int i){
  int index;
  string Instruction;
    int pos = instructions[i].input.find(":");
    if(pos>0)
    {
      index = pos + 1;
    }else
    {
      index = 0;
    }
    int FindSpace = instructions[i].input.find(" ");
    if(FindSpace > 0)
    {
      if(index == 0)
      {
        Instruction = instructions[i].input.substr(index,FindSpace);
      }
      else
      {
        Instruction = instructions[i].input.substr(index,index-2);
      }
  }
  return Instruction;
}

void ReadDataFile(const string& fileName){
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

void ModifyInstructions (vector<vector<string>> labels, vector<Instruction>& instructions) {
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
        //cout<<FindFirstComma<<endl;
        if(FindFirstComma > 0)
        {
          string sub = instructions[i].input.substr(FindFirstComma+1,'\n');
          FindSecondComma = sub.find(",");
          LabelFound = sub.substr(FindSecondComma+1, '\n');
        }
        for(int j =0; j<labels.size();j++)
        {
          if(LabelFound == labels[j][0])
          {
            Difference = stoi(labels[j][1])- numberofLines ;
          }
        }
        int FindSecondCommainALL = FindFirstComma+2+FindSecondComma;
        instructions[i].input.replace(FindSecondCommainALL,instructions[i].input.size()-FindSecondCommainALL,to_string(Difference));
      }
      if(Instruction == instructionsHeadings[33]){
          string LabelFound;
          int FindFirstComma = instructions[i].input.find(",");
          if(FindFirstComma > 0){
            LabelFound = instructions[i].input.substr(FindFirstComma+1, '\n');
            //cout<<LabelFound<<endl;
          }
          for(int j =0; j<labels.size();j++)
          {
            if(LabelFound == labels[j][0])
            {
              Difference = stoi(labels[j][1])- numberofLines ;
            }
          }
          instructions[i].input.replace(FindFirstComma+1,instructions[i].input.size()-FindFirstComma+1,to_string(Difference));
        }
        int FindLabel = instructions[i].input.find(":");
        instructions[i].input = instructions[i].input.substr(FindLabel+1 , instructions[i].input.size());
        if(instructions[i].input.size() < 2){
          instructions.erase(instructions.begin() + i);
        }
      numberofLines +=4;
    }
}

void Three_Registers(string& instruction, string &rd, string &rs1 , string &rs2){
    int FindSpace = instruction.find(" ");
    if(FindSpace > 0){
      string sub1 = instruction.substr(FindSpace+1, '\n');
      int FindFirstComma = sub1.find(",");
      rd = instruction.substr(FindSpace+1, FindFirstComma);
        if(rd[0] != 'x'){
        ModifyReg(rd);
        
            instruction.replace(FindSpace+1, FindFirstComma, rd);}
      //cout<<rd<<endl;
      string sub2 = sub1.substr(FindFirstComma+1, '\n');
      int FindSecondComma = sub2.find(",");
      rs1 = sub1.substr(FindFirstComma+1, FindSecondComma);
      //cout<<"rs1 "<<rs1<<endl;
      if(rs1[0] != 'x'){
        //cout<<"ay7aga??"<<endl;
        ModifyReg(rs1);
        if(rd.size() == 2){
            instruction.replace(FindSpace+FindFirstComma+2,FindSecondComma, rs1);
            }
        else if(rd.size()>2 && rs1.size() == 2){
          //cout<<"Here1 "<<instruction<<endl;
            instruction.replace(FindSpace+FindFirstComma+4,FindSecondComma, rs1);
         }else if (rd.size() > 2 && rs1.size()>2){
           //cout<<"Here "<<instruction<<"size: "<<instruction.size()<<endl;
            instruction.replace(FindSpace+FindFirstComma+3,FindSecondComma, rs1);
         }
      }
      rs2 = sub2.substr(FindSecondComma+1, '\n');
      //cout<<"rs2 "<<rs2<<endl;
        if(isNumber(rs2) == false){
            if(rs2[0] != 'x'){
              ModifyReg(rs2);
            if (rs1.size() == 2) {
                instruction.replace(FindSpace+FindFirstComma+FindSecondComma+3,instruction.size()-FindSecondComma+2, rs2);}
            else if(rs1.size() != 2 && rd.size() == 2){
                instruction.replace(FindSpace+FindFirstComma+FindSecondComma+4,instruction.size()-FindSecondComma+2, rs2);
            }
            else {
                instruction.replace(FindSpace+FindFirstComma+FindSecondComma+5,instruction.size()-FindSecondComma+2, rs2);
            }
        }
        }
        //cout<<instruction<<endl;
      //cout<<rs2<<endl;
    }
}

void Two_Registers_OffSet(string &instruction, string &rd, string &rs1 , int &OffSet){
    int FindSpace = instruction.find(" ");
    if(FindSpace > 0){
      string sub1 = instruction.substr(FindSpace+1 , '\n');
      int FindFirstComma = sub1.find(",");
      rd = instruction.substr(FindSpace+1, FindFirstComma);
      if(rd[0] != 'x'){
      ModifyReg(rd);
      instruction.replace(FindSpace+1, FindFirstComma, rd);}
      //cout<<rd<<endl;
      string sub2 = sub1.substr(FindFirstComma+1, '\n');
      int FindFirstBracket = sub2.find("(");
      string OffSet_string = sub1.substr(FindFirstComma+1, FindFirstBracket);
      OffSet = stoi(OffSet_string);
      //cout<<OffSet<<endl;
      string sub3 = sub2.substr(FindFirstBracket+1,'\n');
      int FindSecondBracket = sub3.find(")");
      rs1 = sub2.substr(FindFirstBracket+1, FindSecondBracket);
      if(rs1[0] != 'x'){
      ModifyReg(rs1);
      if(rd.size() == 2){
          instruction.replace(FindSpace+FindFirstComma+FindFirstBracket+3,FindSecondBracket,rs1);}
      else{
          instruction.replace(FindSpace+FindFirstComma+FindFirstBracket+4,FindSecondBracket,rs1);
       }
      }
      //cout<<rs1<<endl;
     }
}

void Register_imm(string &instruction, string &rd, string &imm){
    int FindSpace = instruction.find(" ");
    if(FindSpace > 0){
      string sub1 = instruction.substr(FindSpace+1, '\n');
      int FindFirstComma = sub1.find(",");
      rd = instruction.substr(FindSpace+1, FindFirstComma);
      if(rd[0] != 'x'){
      ModifyReg(rd);
      instruction.replace(FindSpace+1, FindFirstComma, rd);}
      //cout<<"rd " <<rd<<endl;
      imm = sub1.substr(FindFirstComma+1, '\n');
      //cout<<"rs1 "<<rs1<<endl;
    }
}

int binary_to_dec(string input)
{
    int binary = stoi(input);
    int decimal = 0;
    int rem = 0;

    for (int i = 0; binary > 0; i++)
    {
        rem = binary % 10;
        decimal += rem * pow(2, i);
        binary = binary / 10;
    }

    return decimal;
}

string dec_to_binary(int number)
{
    int binary[8];
    string temp="";

    for (int i = 0; i < 8; i++)
        binary[i] = 0;

    for (int i = 0; number > 0; i++)
    {
        binary[7 - i] = number % 2;
        number = number / 2;
    }

    for (int i = 0; i < 8; i++)
        temp += to_string(binary[i]);

    return temp;
}

int get_index(string reg)
{
  string temp = reg;
  temp = temp.substr(1,temp.size());
  return stoi(temp);
}

void lui(string &instruction)
{
    string rd, imm_s;
    Register_imm(instruction, rd, imm_s);
    int imm= stoi(imm_s);
    int temp = imm*4096; //shift 12 bits
    regFile[get_index(rd)]=regFile[get_index(rd)] + temp;
    PC+=4;
}

void auipc(string &instruction)
{
    string rd, imm_s;
    Register_imm(instruction, rd, imm_s);
    int imm= stoi(imm_s);
    regFile[get_index(rd)]=(imm*4096)+PC; //shift 12 bits
    PC+=4;
}

void jal(string &instruction)
{
    string rd, imm_s;
    Register_imm(instruction, rd, imm_s);
    int imm = stoi(imm_s);
    regFile[get_index(rd)] = PC+4;
    PC+=imm;
}

void jalr(string &instruction)
{
    string rd, rs1;
    int offset;
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    regFile[get_index(rd)] = PC+4;
    PC = regFile[get_index(rs1)] + offset;
}

void lb(string &instruction)
{
    string rd,rs1;
    int offset;
    string final_bin = "";
    int number;
    
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    
    for(int i = 0; i < stored_adresses.size();i++)
      if(stored_adresses[i] == address)
         number= stored_values[i];

    
    string binary = dec_to_binary(number);
    while(binary.size() < 32)
    {
      binary = '0' + binary;
    }
    for(int i = 23; i < 32; i++)
      final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = binary_to_dec(final_bin);
    PC+=4;
}

void lh(string &instruction)
{
    string rd,rs1;
    int offset;
    string final_bin = "";
    int number;
  
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    for(int i = 0; i < stored_adresses.size();i++)
      if(stored_adresses[i] == address)
         number= stored_values[i];
    string binary = dec_to_binary(number);
    while(binary.size() < 32)
    {
      binary = '0' + binary;
    }
    for(int i = 15; i < 32; i++)
      final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = binary_to_dec(final_bin);
    
    PC+=4;
}

void lbu (string &instruction)
{
    string rd,rs1;
    int offset;
    string final_bin = "";
    int number;
    
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    
    for(int i = 0; i < stored_adresses.size();i++)
      if(stored_adresses[i] == address)
         number= stored_values[i];

    int temp = number <<24 >>24;
    // string binary = dec_to_binary(number);
    // while(binary.size() < 32)
    // {
    //   binary = '0' + binary;
    // }
    // for(int i = 23; i < 32; i++)
    //   final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = temp;
    
    PC+=4;
}

void lhu (string &instruction)
{
    string rd,rs1;
    int offset;
    string final_bin = "";
    int number;
    
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    
    for(int i = 0; i < stored_adresses.size();i++)
      if(stored_adresses[i] == address)
         number= stored_values[i];

    int temp = number <<16 >>16;
    // string binary = dec_to_binary(number);
    // while(binary.size() < 32)
    // {
    //   binary = '0' + binary;
    // }
    // for(int i = 23; i < 32; i++)
    //   final_bin = final_bin + binary[i];
    regFile[get_index(rd)] = temp;
    
    PC+=4;
}

void beq(string &instruction)
{
    string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate=stoi(imm);
    
    if(regFile[get_index(rs1)]==regFile[get_index(rs2)])
    {
        PC+=immediate;
    }
    else
    {
        PC+=4;
    }
}

void bne(string &instruction)
{
    string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate=stoi(imm);
    
    if(regFile[get_index(rs1)]!=regFile[get_index(rs2)])
    {
        PC+=immediate;
    }
    else
    {
        PC+=4;
    }
}

void bltu(string &instruction)
{
    string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate=stoi(imm);
    
    if((unsigned int)regFile[get_index(rs1)] < (unsigned int)regFile[get_index(rs2)])
    {
        PC+=immediate;
    }
    else
    {
        PC+=4;
    }
}

void bgeu(string &instruction)
{
    string rs1, rs2, imm;
    Three_Registers(instruction, rs1, rs2, imm);
    int immediate=stoi(imm);
    
    if((unsigned int)regFile[get_index(rs1)] >= (unsigned int)regFile[get_index(rs2)])
    {
        PC+=immediate;
    }
    else
    {
        PC+=4;
    }
}

void lw(string &instruction)
{
    string rd, rs1;
    int offset;
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    for(int i = 0; i < stored_adresses.size();i++)
      {
        if(stored_adresses[i] == address)
        {
          regFile[get_index(rd)] = stored_values[i];
        }
      }
    PC = PC + 4;
}

void blt (string &instruction){
  string rs2,rs1,imm_s;
  int imm;
  Three_Registers(instruction, rs1, rs2 ,imm_s);
  imm = stoi(imm_s);

  if(regFile[get_index(rs1)] < regFile[get_index(rs2)])
    PC += imm;
  else
    PC += 4;
}

void bge (string &instruction){
  string rs1,rs2,imm_s;
  int imm;
  Three_Registers(instruction, rs1, rs2 ,imm_s);
  imm = stoi(imm_s);

  if(regFile[get_index(rs1)] >= regFile[get_index(rs2)])
    PC += imm;
  else
    PC += 4;
}

void addi(string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
    PC += 4;
}

void xori (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
    PC += 4;
}

void sb (string &instruction){
    bool flag = false;
    string rd,rs1;
    int offset;
    string final_bin = "";
    Two_Registers_OffSet(instruction, rd, rs1, offset);
     int address = regFile[get_index(rs1)] + offset;
    string binary = dec_to_binary(regFile[get_index(rd)]);
    while(binary.size() < 32)
    {
      binary = '0' + binary;
    }
    for(int i = 23; i < 32; i++){
      final_bin = final_bin + binary[i];}
    for(int i = 0; i < stored_adresses.size();i++){
      if(stored_adresses[i] == address){
         stored_values[i] = binary_to_dec(final_bin);
         flag = true;
         break;
         }
    }
    if (!flag){
      stored_adresses.push_back(address);
      stored_values.push_back(binary_to_dec(final_bin));
    }
    PC += 4;
}

void sh (string &instruction){
    bool flag = false;
    string rd,rs1;
    int offset;
    string final_bin = "";
    
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;

    string binary = dec_to_binary(regFile[get_index(rd)]);
    while(binary.size() < 32)
    {
      binary = '0' + binary;
    }
    for(int i = 15; i < 32; i++){
      final_bin = final_bin + binary[i];}
    for(int i = 0; i < stored_adresses.size();i++){
      if(stored_adresses[i] == address){
         stored_values[i] = binary_to_dec(final_bin);
         flag = true;
         break;
         }
    }
    if (!flag){
      stored_adresses.push_back(address);
      stored_values.push_back(binary_to_dec(final_bin));
    }
    PC += 4;
}

void sw (string &instruction){
    bool flag = false;
    string rd,rs1;
    int offset;
    Two_Registers_OffSet(instruction, rd, rs1, offset);
    int address = regFile[get_index(rs1)] + offset;
    for(int i = 0; i < stored_adresses.size();i++)
    {
      if(stored_adresses[i] == address)
         {
           stored_values[i] = regFile[get_index(rd)];
           flag = true;
           break;
         }
    }
    if (!flag){
      stored_adresses.push_back(address);
      stored_values.push_back(regFile[get_index(rd)]);
    }
    PC = PC+4;
}

void slti (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);

    if(regFile[get_index(rs1)] < imm)
      regFile[get_index(rd)] = 1;
    else
      regFile[get_index(rd)] = 0;
    PC += 4;
}

void sltiu (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    if(regFile[get_index(rs1)] < imm)
      regFile[get_index(rd)] = 1;
    else
      regFile[get_index(rd)] = 0;
    PC += 4;
}

void ori(string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    regFile[get_index(rd)] = regFile[get_index(rs1)] | imm;
     PC += 4;
}

void andi (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    regFile[get_index(rd)] = regFile[get_index(rs1)] & imm;
    PC += 4;
}

void slli (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    regFile[get_index(rd)] = regFile[get_index(rs1)] << imm;
    PC += 4;
}

void srli (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    regFile[get_index(rd)] = regFile[get_index(rs1)] >> imm;
    PC += 4;
}

void srai (string &instruction){
    string rd,rs1,imm_s;
    int imm;
    Three_Registers(instruction, rd, rs1 ,imm_s);
    imm = stoi(imm_s);
    
    regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)imm;
    PC += 4;
}

void add(string& instruction){
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] + regFile[get_index(rs2)];
  PC += 4;
}

void sub(string& instruction){
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] - regFile[get_index(rs2)];
  PC += 4;
}

void sll(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] << regFile[get_index(rs2)];
  PC += 4;
}

void slt(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  if(regFile[get_index(rs1)] < regFile[get_index(rs2)])
  regFile[get_index(rd)] = 1;
  else
  regFile[get_index(rd)] = 0;
  PC += 4;
}

void sltu(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] << (unsigned int)regFile[get_index(rs2)];
  PC += 4;
}

void x_or(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] ^ regFile[get_index(rs2)];
  PC += 4;
}

void srl(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] >> regFile[get_index(rs2)];
  PC += 4;
}

void sra(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)regFile[get_index(rs2)];
  PC += 4;
}

void or_instruction(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  regFile[get_index(rd)] = regFile[get_index(rs1)] | regFile[get_index(rs2)];
  PC += 4;
}

void and_instruction(string& instruction)
{
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);
  
  regFile[get_index(rd)] = regFile[get_index(rs1)] & regFile[get_index(rs2)];
  PC += 4;
}

void mul (string& instruction){
  string rd,rs1,rs2;
  cout<<"WE ARE HERE"<<endl;
  Three_Registers(instruction,rd,rs1,rs2);

 long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
 regFile[get_index(rd)] = x & (0x00000000FFFFFFFF);

 PC +=4;
}

void mulH (string& instruction){
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

 long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
 regFile[get_index(rd)] = x>> 32;

 PC +=4;
}

void mulHU (string& instruction){
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

 unsigned long int x = (unsigned long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
 regFile[get_index(rd)] = x>> 32;

 PC +=4;
}

void mulHSU (string& instruction){
  string rd,rs1,rs2;
  Three_Registers(instruction,rd,rs1,rs2);

  unsigned long int x = (signed long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
 regFile[get_index(rd)] = x>> 32;

 PC +=4;
}

void div (string &instruction){
  string rd,rs1,rs2;
  int result;
  Three_Registers(instruction,rd,rs1,rs2);

  if(regFile[get_index(rs2)]==0){ //dividing by zero
    result = -1;
  }else if (regFile[get_index(rs1)]==0x80000000&&regFile[get_index(rs2)]==-1){ //overflow
    result = 0x80000000; //-2^XLEN-1
  }else{
    result = regFile[get_index(rs1)] / regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC +=4;
}

void divu (string &instruction){
  string rd,rs1,rs2;
  unsigned int result;
  Three_Registers(instruction,rd,rs1,rs2);

  if(regFile[get_index(rs2)]==0){ //dividing by zero
    result = 0xFFFFFFFF; //(2^XLen)-1
  }else{
    result = (unsigned int)regFile[get_index(rs1)] / ( unsigned int)regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC +=4;
}

void rem(string &instruction){
  string rd,rs1,rs2;
  int result;
  Three_Registers (instruction,rd,rs1,rs2);

  if(regFile[get_index(rs2)] == 0){
    result = regFile[get_index(rs1)];
  }else if(regFile[get_index(rs1)]==0x80000000&&regFile[get_index(rs2)]==-1){
    result = 0;
  }else{
    result = regFile[get_index(rs1)] % regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC +=4;
}

void remu(string &instruction){
  string rd,rs1,rs2;
  unsigned int result;
  Three_Registers (instruction,rd,rs1,rs2);

  if(regFile[get_index(rs2)] == 0){
    result = regFile[get_index(rs1)];
  }else{
    result = (unsigned int)regFile[get_index(rs1)] % (unsigned int)regFile[get_index(rs2)];
  }

  regFile[get_index(rd)] = result;

  PC +=4;
}

void DecideType(vector<Instruction> &instructions){
        if(GetInstruction(instructions, ((PC-starting_address)/4)) == "addi")
        {
          addi(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "lbu")
        {
            lbu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "lhu")
        {
            lhu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sb")
        {
            sb(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sh")
        {
            sh(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sw")
        {
            sw(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "slti"){
            slti(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sltiu")
        {
            sltiu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "xori"){
            xori(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "ori")
        {
            ori(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "andi"){
            andi(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "slli"){
            slli(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "srli"){
            srli(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "srai"){
            srai(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "add")
        {
            add(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sub")
        {
            sub(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sll")
        {
            sll(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "slt")
        {
            slt(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "srai"){
            srai(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sltu"){
            sltu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "xor")
        {
            x_or(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "srl")
        {
            srl(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "sra")
        {
            sra(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "or")
        {
            or_instruction(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "and")
        {
            and_instruction(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "bge")
        {
            bge(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "blt")
        {
            blt(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "lw")
        {
            lw(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "lh")
        {
            lh(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "lb")
        {
            lb(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "bgeu"){
            bgeu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "bltu"){
            bltu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "bne")
        {
            bne(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "beq")
        {
            beq(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "jalr"){
            jalr(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "jal")
        {
            jal(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "auipc")
        {
            auipc(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "lui")
        {
            lui(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "fence")
        {
            cout<<"FENCE instruction stops the program"<<endl;
            exit(EXIT_SUCCESS);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "ecall")
        {
            cout<<"ECALL instruction stops the program"<<endl;
            exit(EXIT_SUCCESS);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "ebreak")
        {
            cout<<"EBREAK instruction stops the program"<<endl;
            exit(EXIT_SUCCESS);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "mul")
        {
            mul(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "mulh")
        {
            mulH(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "mulhu")
        {
            mulHU(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "mulhsu")
        {
            mulHSU(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "div")
        {
            div(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "divu")
        {
            divu(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "rem")
        {
            rem(instructions[((PC-starting_address)/4)].input);
        }
        else if (GetInstruction(instructions, ((PC-starting_address)/4)) == "remu")
        {
            remu(instructions[((PC-starting_address)/4)].input);
        }
}

void callFunctions(){
  auto instructions = ReadFile(path);
  ReadDataFile(path2);
  auto labels = StoreLabels();
  ModifyInstructions(labels, instructions);

  cout<<"Original Code: "<<endl;
  for(int i=0;i<instructions.size();i++){
    cout<<instructions[i].input <<endl;
  }
  cout<<endl;

  if(instructions[instructions.size()-1].input.size() < 2){
    MAX_PC =starting_address + (instructions.size() * 4) - 8;
  }else{
    MAX_PC =starting_address + (instructions.size() * 4) - 4;}

//cout<<"MAX_PC"<<MAX_PC<<endl;
  while(PC <= MAX_PC){
   cout<<"PC: "<<endl;
   cout<<"Dec: "<<dec<<PC<<"  "<<"Hex: "<<hex<<PC<<"  "<<"Bin: "<<dec_to_binary(PC)<<endl;
   DecideType(instructions);

  cout<<"Reg File contents after instruction "<< ((PC-starting_address)/4)<<endl;
  regFile[0] = 0;
  for(int i=0;i<32;i++){
    cout <<"x"<<dec<<i<<"---> "<<"Dec: "<< dec<<regFile[i] <<"  "<<"Hex: "<<hex<<regFile[i]<<"  "<<"Bin: "<<dec_to_binary(regFile[i])<< endl;
  }
  cout << endl;
  
  cout << "Memory Content:" << endl;
  for(int i = 0; i < stored_adresses.size();i++)
  {
    cout<<"Dec: ";
    cout << dec<<stored_adresses[i] << "," <<dec<< stored_values[i]<<"//";

    cout<<"Hex: ";
    cout << hex<<stored_adresses[i] << "," <<hex<< stored_values[i] << "//";

    cout<<"Bin: ";
    cout << dec_to_binary(stored_adresses[i]) << "," << dec_to_binary(stored_values[i]) << endl;

  }
  cout<<"----------------------------"<<endl;
  cout<<endl;
  }
  cout<<endl;

  cout<<"Basic Code: "<<endl;
  for(int i=0;i<instructions.size();i++){
    cout<<instructions[i].input<<endl;
  }
  cout<<endl;

}

int main()
{
    cout<<"What is the program's starting Address?"<<endl;
    cin>>starting_address;
    PC = starting_address;
    callFunctions();
    return 0;
}
