#include "defs.h"
#include "std++.hpp"
#include "globals.hpp"

int main()
{
  std::cout << "What is the program's starting Address?" << std::endl;
  std::cin >> starting_address;
  PC = starting_address;
  initialize();
  std::ostream &outs = std::cout;

  simulate(outs);

  return 0;
}
