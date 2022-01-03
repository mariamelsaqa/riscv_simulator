SRC= main.cpp parse.cpp utils.cpp globals.cpp instructions/*.cpp
HEADERS= ops.hpp defs.h globals.hpp instruction.hpp
GCC= g++
RISCV_SIM= riscv_simulator
CFLAGS= -I


$(RISCV_SIM): $(SRC) $(HEADERS)
		$(GCC) $(SRC) $(CFLAGS) ./ -o $(RISCV_SIM)