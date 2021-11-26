

// void lui(string &instruction)
// {
//     string rd, imm_s;
//     Register_imm(instruction, rd, imm_s);
//     int imm = stoi(imm_s);
//     int temp = imm * 4096; //shift 12 bits
//     regFile[get_index(rd)] = regFile[get_index(rd)] + temp;
//     PC += 4;
// }

// void auipc(string &instruction)
// {
//     string rd, imm_s;
//     Register_imm(instruction, rd, imm_s);
//     int imm = stoi(imm_s);
//     regFile[get_index(rd)] = (imm * 4096) + PC; //shift 12 bits
//     PC += 4;
// }

// void jal(string &instruction)
// {
//     string rd, imm_s;
//     Register_imm(instruction, rd, imm_s);
//     int imm = stoi(imm_s);
//     regFile[get_index(rd)] = PC + 4;
//     PC += imm;
// }

// void jalr(string &instruction)
// {
//     string rd, rs1;
//     int offset;
//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     regFile[get_index(rd)] = PC + 4;
//     PC = regFile[get_index(rs1)] + offset;
// }

// void lb(string &instruction)
// {
//     string rd, rs1;
//     int offset;
//     string final_bin = "";
//     int number;

//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;

//     for (int i = 0; i < stored_adresses.size(); i++)
//         if (stored_adresses[i] == address)
//             number = stored_values[i];

//     string binary = dec_to_binary(number);
//     while (binary.size() < 32)
//     {
//         binary = '0' + binary;
//     }
//     for (int i = 23; i < 32; i++)
//         final_bin = final_bin + binary[i];
//     regFile[get_index(rd)] = binary_to_dec(final_bin);
//     PC += 4;
// }

// void lh(string &instruction)
// {
//     string rd, rs1;
//     int offset;
//     string final_bin = "";
//     int number;

//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;
//     for (int i = 0; i < stored_adresses.size(); i++)
//         if (stored_adresses[i] == address)
//             number = stored_values[i];
//     string binary = dec_to_binary(number);
//     while (binary.size() < 32)
//     {
//         binary = '0' + binary;
//     }
//     for (int i = 15; i < 32; i++)
//         final_bin = final_bin + binary[i];
//     regFile[get_index(rd)] = binary_to_dec(final_bin);

//     PC += 4;
// }

// void lbu(string &instruction)
// {
//     string rd, rs1;
//     int offset;
//     string final_bin = "";
//     int number;

//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;

//     for (int i = 0; i < stored_adresses.size(); i++)
//         if (stored_adresses[i] == address)
//             number = stored_values[i];

//     int temp = number << 24 >> 24;
//     // string binary = dec_to_binary(number);
//     // while(binary.size() < 32)
//     // {
//     //   binary = '0' + binary;
//     // }
//     // for(int i = 23; i < 32; i++)
//     //   final_bin = final_bin + binary[i];
//     regFile[get_index(rd)] = temp;

//     PC += 4;
// }

// void lhu(string &instruction)
// {
//     string rd, rs1;
//     int offset;
//     string final_bin = "";
//     int number;

//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;

//     for (int i = 0; i < stored_adresses.size(); i++)
//         if (stored_adresses[i] == address)
//             number = stored_values[i];

//     int temp = number << 16 >> 16;
//     // string binary = dec_to_binary(number);
//     // while(binary.size() < 32)
//     // {
//     //   binary = '0' + binary;
//     // }
//     // for(int i = 23; i < 32; i++)
//     //   final_bin = final_bin + binary[i];
//     regFile[get_index(rd)] = temp;

//     PC += 4;
// }

// void beq(string &instruction)
// {
//     string rs1, rs2, imm;
//     Three_Registers(instruction, rs1, rs2, imm);
//     int immediate = stoi(imm);

//     if (regFile[get_index(rs1)] == regFile[get_index(rs2)])
//     {
//         PC += immediate;
//     }
//     else
//     {
//         PC += 4;
//     }
// }

// void bne(string &instruction)
// {
//     string rs1, rs2, imm;
//     Three_Registers(instruction, rs1, rs2, imm);
//     int immediate = stoi(imm);

//     if (regFile[get_index(rs1)] != regFile[get_index(rs2)])
//     {
//         PC += immediate;
//     }
//     else
//     {
//         PC += 4;
//     }
// }

// void bltu(string &instruction)
// {
//     string rs1, rs2, imm;
//     Three_Registers(instruction, rs1, rs2, imm);
//     int immediate = stoi(imm);

//     if ((unsigned int)regFile[get_index(rs1)] < (unsigned int)regFile[get_index(rs2)])
//     {
//         PC += immediate;
//     }
//     else
//     {
//         PC += 4;
//     }
// }

// void bgeu(string &instruction)
// {
//     string rs1, rs2, imm;
//     Three_Registers(instruction, rs1, rs2, imm);
//     int immediate = stoi(imm);

//     if ((unsigned int)regFile[get_index(rs1)] >= (unsigned int)regFile[get_index(rs2)])
//     {
//         PC += immediate;
//     }
//     else
//     {
//         PC += 4;
//     }
// }

// void lw(string &instruction)
// {
//     string rd, rs1;
//     int offset;
//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;
//     for (int i = 0; i < stored_adresses.size(); i++)
//     {
//         if (stored_adresses[i] == address)
//         {
//             regFile[get_index(rd)] = stored_values[i];
//         }
//     }
//     PC = PC + 4;
// }

// void blt(string &instruction)
// {
//     string rs2, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rs1, rs2, imm_s);
//     imm = stoi(imm_s);

//     if (regFile[get_index(rs1)] < regFile[get_index(rs2)])
//         PC += imm;
//     else
//         PC += 4;
// }

// void bge(string &instruction)
// {
//     string rs1, rs2, imm_s;
//     int imm;
//     Three_Registers(instruction, rs1, rs2, imm_s);
//     imm = stoi(imm_s);

//     if (regFile[get_index(rs1)] >= regFile[get_index(rs2)])
//         PC += imm;
//     else
//         PC += 4;
// }

// void addi(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);
//     regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
//     PC += 4;
// }

// void xori(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] + imm;
//     PC += 4;
// }

// void sb(string &instruction)
// {
//     bool flag = false;
//     string rd, rs1;
//     int offset;
//     string final_bin = "";
//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;
//     string binary = dec_to_binary(regFile[get_index(rd)]);
//     while (binary.size() < 32)
//     {
//         binary = '0' + binary;
//     }
//     for (int i = 23; i < 32; i++)
//     {
//         final_bin = final_bin + binary[i];
//     }
//     for (int i = 0; i < stored_adresses.size(); i++)
//     {
//         if (stored_adresses[i] == address)
//         {
//             stored_values[i] = binary_to_dec(final_bin);
//             flag = true;
//             break;
//         }
//     }
//     if (!flag)
//     {
//         stored_adresses.push_back(address);
//         stored_values.push_back(binary_to_dec(final_bin));
//     }
//     PC += 4;
// }

// void sh(string &instruction)
// {
//     bool flag = false;
//     string rd, rs1;
//     int offset;
//     string final_bin = "";

//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;

//     string binary = dec_to_binary(regFile[get_index(rd)]);
//     while (binary.size() < 32)
//     {
//         binary = '0' + binary;
//     }
//     for (int i = 15; i < 32; i++)
//     {
//         final_bin = final_bin + binary[i];
//     }
//     for (int i = 0; i < stored_adresses.size(); i++)
//     {
//         if (stored_adresses[i] == address)
//         {
//             stored_values[i] = binary_to_dec(final_bin);
//             flag = true;
//             break;
//         }
//     }
//     if (!flag)
//     {
//         stored_adresses.push_back(address);
//         stored_values.push_back(binary_to_dec(final_bin));
//     }
//     PC += 4;
// }

// void sw(string &instruction)
// {
//     bool flag = false;
//     string rd, rs1;
//     int offset;
//     Two_Registers_OffSet(instruction, rd, rs1, offset);
//     int address = regFile[get_index(rs1)] + offset;
//     for (int i = 0; i < stored_adresses.size(); i++)
//     {
//         if (stored_adresses[i] == address)
//         {
//             stored_values[i] = regFile[get_index(rd)];
//             flag = true;
//             break;
//         }
//     }
//     if (!flag)
//     {
//         stored_adresses.push_back(address);
//         stored_values.push_back(regFile[get_index(rd)]);
//     }
//     PC = PC + 4;
// }

// void slti(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     if (regFile[get_index(rs1)] < imm)
//         regFile[get_index(rd)] = 1;
//     else
//         regFile[get_index(rd)] = 0;
//     PC += 4;
// }

// void sltiu(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     if (regFile[get_index(rs1)] < imm)
//         regFile[get_index(rd)] = 1;
//     else
//         regFile[get_index(rd)] = 0;
//     PC += 4;
// }

// void ori(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] | imm;
//     PC += 4;
// }

// void andi(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] & imm;
//     PC += 4;
// }

// void slli(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] << imm;
//     PC += 4;
// }

// void srli(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] >> imm;
//     PC += 4;
// }

// void srai(string &instruction)
// {
//     string rd, rs1, imm_s;
//     int imm;
//     Three_Registers(instruction, rd, rs1, imm_s);
//     imm = stoi(imm_s);

//     regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)imm;
//     PC += 4;
// }

// void add(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] + regFile[get_index(rs2)];
//     PC += 4;
// }

// void sub(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] - regFile[get_index(rs2)];
//     PC += 4;
// }

// void sll(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] << regFile[get_index(rs2)];
//     PC += 4;
// }

// void slt(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     if (regFile[get_index(rs1)] < regFile[get_index(rs2)])
//         regFile[get_index(rd)] = 1;
//     else
//         regFile[get_index(rd)] = 0;
//     PC += 4;
// }

// void sltu(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] << (unsigned int)regFile[get_index(rs2)];
//     PC += 4;
// }

// void x_or(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] ^ regFile[get_index(rs2)];
//     PC += 4;
// }

// void srl(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] >> regFile[get_index(rs2)];
//     PC += 4;
// }

// void sra(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = (unsigned int)regFile[get_index(rs1)] >> (unsigned int)regFile[get_index(rs2)];
//     PC += 4;
// }

// void or_instruction(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] | regFile[get_index(rs2)];
//     PC += 4;
// }

// void and_instruction(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     regFile[get_index(rd)] = regFile[get_index(rs1)] & regFile[get_index(rs2)];
//     PC += 4;
// }

// void mul(string &instruction)
// {
//     string rd, rs1, rs2;
//     cout << "WE ARE HERE" << endl;
//     Three_Registers(instruction, rd, rs1, rs2);

//     long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
//     regFile[get_index(rd)] = x & (0x00000000FFFFFFFF);

//     PC += 4;
// }

// void mulH(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     long int x = (long int)regFile[get_index(rs1)] * (long int)regFile[get_index(rs2)];
//     regFile[get_index(rd)] = x >> 32;

//     PC += 4;
// }

// void mulHU(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     unsigned long int x = (unsigned long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
//     regFile[get_index(rd)] = x >> 32;

//     PC += 4;
// }

// void mulHSU(string &instruction)
// {
//     string rd, rs1, rs2;
//     Three_Registers(instruction, rd, rs1, rs2);

//     unsigned long int x = (signed long int)regFile[get_index(rs1)] * (unsigned long int)regFile[get_index(rs2)];
//     regFile[get_index(rd)] = x >> 32;

//     PC += 4;
// }

// void div(string &instruction)
// {
//     string rd, rs1, rs2;
//     int result;
//     Three_Registers(instruction, rd, rs1, rs2);

//     if (regFile[get_index(rs2)] == 0)
//     { //dividing by zero
//         result = -1;
//     }
//     else if (regFile[get_index(rs1)] == 0x80000000 && regFile[get_index(rs2)] == -1)
//     {                        //overflow
//         result = 0x80000000; //-2^XLEN-1
//     }
//     else
//     {
//         result = regFile[get_index(rs1)] / regFile[get_index(rs2)];
//     }

//     regFile[get_index(rd)] = result;

//     PC += 4;
// }

// void divu(string &instruction)
// {
//     string rd, rs1, rs2;
//     unsigned int result;
//     Three_Registers(instruction, rd, rs1, rs2);

//     if (regFile[get_index(rs2)] == 0)
//     {                        //dividing by zero
//         result = 0xFFFFFFFF; //(2^XLen)-1
//     }
//     else
//     {
//         result = (unsigned int)regFile[get_index(rs1)] / (unsigned int)regFile[get_index(rs2)];
//     }

//     regFile[get_index(rd)] = result;

//     PC += 4;
// }

// void rem(string &instruction)
// {
//     string rd, rs1, rs2;
//     int result;
//     Three_Registers(instruction, rd, rs1, rs2);

//     if (regFile[get_index(rs2)] == 0)
//     {
//         result = regFile[get_index(rs1)];
//     }
//     else if (regFile[get_index(rs1)] == 0x80000000 && regFile[get_index(rs2)] == -1)
//     {
//         result = 0;
//     }
//     else
//     {
//         result = regFile[get_index(rs1)] % regFile[get_index(rs2)];
//     }

//     regFile[get_index(rd)] = result;

//     PC += 4;
// }

// void remu(string &instruction)
// {
//     string rd, rs1, rs2;
//     unsigned int result;
//     Three_Registers(instruction, rd, rs1, rs2);

//     if (regFile[get_index(rs2)] == 0)
//     {
//         result = regFile[get_index(rs1)];
//     }
//     else
//     {
//         result = (unsigned int)regFile[get_index(rs1)] % (unsigned int)regFile[get_index(rs2)];
//     }

//     regFile[get_index(rd)] = result;

//     PC += 4;
// }
