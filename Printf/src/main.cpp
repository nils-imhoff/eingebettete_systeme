#include "../include/Printf.h"
static const unsigned int STRING_LENGTH = 300;

int main()
{
    char print[STRING_LENGTH];
    char *returnString = Printf(print, print + STRING_LENGTH, "int: %d\nuint: %u\nchar: %c\nstring: %s\n-hex: %x\nhex: %x\n-bin: %b\nbin: %b\nprozent: %%\n", -94, 3, 'n', "test", -2048, 4605, -42, 42);
    if (returnString)
        return 0;
    else
        return 1;
}
