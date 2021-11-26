#include "utils.h"
//utils
bool isNumber(string line)
{
    char *p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

//utils
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
//utils
string dec_to_binary(int number)
{
    int binary[8];
    string temp = "";

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