
#include "defs.h"
#include "std++.hpp"
#include "globals.hpp"

static void execute()
{
    int instIndex = (PC - starting_address) / 4;
    std::string input = inst_mem[instIndex].input;

    std::string instName = GetInstName(inst_mem, instIndex);
    int instOp = getInstOp(instName);
    auto find = instMap.find(instOp);

    if (find == instMap.end())
        throw_err("Error! Unsupported instruction: " + instName);

    // else
    instFunc_t instFunc = find->second;
    instFunc(input);
}

void initialize()
{
    inst_mem = ReadInstFile(path);
    ReadDataFile(path2);
    auto labels = StoreLabels();
    ModifyInstructions(labels, inst_mem);

    int diff = (inst_mem.end()->input.size() < 2) ? 8 : 4;
    MAX_PC = starting_address + (inst_mem.size() * 4) - diff;

    // if (inst_mem[inst_mem.size() - 1].input.size() < 2)
    //     MAX_PC = starting_address + (inst_mem.size() * 4) - 8;
    // else
    //     MAX_PC = starting_address + (inst_mem.size() * 4) - 4;
}

void simulate(std::ostream &outs)
{

    outs << "----------Original Code----------";
    print_inst_memory(outs);

    while (PC <= MAX_PC)
    {
        outs << "PC: " << std::endl;
        print_all_bases(PC, outs);

        execute();
        regFile[0] = 0;

        print_regfile(outs);
        print_data_memory(outs);
    }

    outs << "----------Basic Code:----------";
    print_inst_memory(outs);
}
