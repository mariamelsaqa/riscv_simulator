#include "defs.h"

inline static void stop_program(const std::string &instName)
{
    std::cout << instName << " instruction stops the program" << std::endl;
    exit(EXIT_SUCCESS);
}
void fence(std::string &instruction)
{
    stop_program("FENCE");
}

void ecall(std::string &instruction)
{
    stop_program("ECALL");
}

void ebreak(std::string &instruction)
{
    stop_program("EBREAK");
}