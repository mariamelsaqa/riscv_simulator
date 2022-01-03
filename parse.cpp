#include "defs.h"
#include "globals.hpp"
#include "std++.hpp"
#include "ops.hpp"
using namespace std;
void ModifyReg(string &reg)
{
    auto found = regNames.find(reg);
    if (found != regNames.end())
        reg = found->second;
}

vector<Instruction> ReadInstFile(const string &fileName) // reads asm instructions
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
    auto instructions = ReadInstFile(path);
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

string GetInstName(const vector<Instruction> &instructions, int i)
{

    string Instruction;
    // if (lbl_pos > 0)
    // {
    //     start_index = lbl_pos + 1;
    // }
    // else
    // {
    //     start_index = 0;
    // }
    int FindSpace = instructions[i].input.find(" ");
    int lbl_pos = instructions[i].input.find(":");

    int start_index = (lbl_pos > 0) ? lbl_pos + 1 : 0;
    int end_index = (start_index == 0) ? FindSpace : start_index - 2;

    if (FindSpace > 0)
        // {
        Instruction = instructions[i].input.substr(start_index, end_index);
    // if (start_index == 0)
    // {
    //     Instruction = instructions[i].input.substr(start_index, FindSpace);
    // }
    // else
    // {
    //     Instruction = instructions[i].input.substr(start_index, start_index - 2);
    // }
    // }
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

static bool isBranch(const std::string &instName)
{

    return instName == instNames[BGE_OP] ||
           instName == instNames[BLT_OP] ||
           instName == instNames[BNE_OP] ||
           instName == instNames[BEQ_OP] ||
           instName == instNames[BLTU_OP] ||
           instName == instNames[BGEU_OP];
}
void ModifyInstructions(vector<vector<string>> labels, vector<Instruction> &instructions)
{
    string Instruction;
    int numberofLines = 0;
    int Difference;
    int start_index;

    for (int i = 0; i < instructions.size(); i++)
    {
        Instruction = GetInstName(instructions, i);
        if (isBranch(Instruction))
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
                if (LabelFound == labels[j][0])
                    Difference = stoi(labels[j][1]) - numberofLines;

            int FindSecondCommainALL = FindFirstComma + 2 + FindSecondComma;
            instructions[i].input.replace(FindSecondCommainALL, instructions[i].input.size() - FindSecondCommainALL, to_string(Difference));
        }
        if (Instruction == instNames[33])
        {
            string LabelFound;
            int FindFirstComma = instructions[i].input.find(",");
            if (FindFirstComma > 0)
            {
                LabelFound = instructions[i].input.substr(FindFirstComma + 1, '\n');
                // cout<<LabelFound<<endl;
            }
            for (int j = 0; j < labels.size(); j++)
                if (LabelFound == labels[j][0])
                    Difference = stoi(labels[j][1]) - numberofLines;

            instructions[i].input.replace(FindFirstComma + 1, instructions[i].input.size() - FindFirstComma + 1, to_string(Difference));
        }
        int FindLabel = instructions[i].input.find(":");
        instructions[i].input = instructions[i].input.substr(FindLabel + 1, instructions[i].input.size());

        if (instructions[i].input.size() < 2)
            instructions.erase(instructions.begin() + i);

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
                instruction.replace(FindSpace + FindFirstComma + 2, FindSecondComma, rs1);
            else if (rd.size() > 2 && rs1.size() == 2)
                // cout<<"Here1 "<<instruction<<endl;
                instruction.replace(FindSpace + FindFirstComma + 4, FindSecondComma, rs1);
            else if (rd.size() > 2 && rs1.size() > 2)
                // cout<<"Here "<<instruction<<"size: "<<instruction.size()<<endl;
                instruction.replace(FindSpace + FindFirstComma + 3, FindSecondComma, rs1);
        }
        rs2 = sub2.substr(FindSecondComma + 1, '\n');
        // cout<<"rs2 "<<rs2<<endl;
        if (isNumber(rs2) == false)
        {
            if (rs2[0] != 'x')
            {
                ModifyReg(rs2);
                if (rs1.size() == 2)
                    instruction.replace(FindSpace + FindFirstComma + FindSecondComma + 3, instruction.size() - FindSecondComma + 2, rs2);
                else if (rs1.size() != 2 && rd.size() == 2)
                    instruction.replace(FindSpace + FindFirstComma + FindSecondComma + 4, instruction.size() - FindSecondComma + 2, rs2);
                else
                    instruction.replace(FindSpace + FindFirstComma + FindSecondComma + 5, instruction.size() - FindSecondComma + 2, rs2);
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
                instruction.replace(FindSpace + FindFirstComma + FindFirstBracket + 3, FindSecondBracket, rs1);
            else
                instruction.replace(FindSpace + FindFirstComma + FindFirstBracket + 4, FindSecondBracket, rs1);
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
