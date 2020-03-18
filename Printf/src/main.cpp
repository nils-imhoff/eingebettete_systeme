#include "../include/Printf.h"

#include <iostream>
static const unsigned int TESTSTRING_LENGTH = 300;

int main() {
    char printHere[TESTSTRING_LENGTH];
    char* formattedString = Printf(printHere, printHere + TESTSTRING_LENGTH, "int: %d\nunsginedint: %u\ncharacter: %c\nstring: %s\nhexaminus: %x\nhexaplus: %x\nbinaryminus: %b\nbinaryplus: %b\nprozentzeichen: %%\n", -74, 3, 'e', "ripx", -3064, 4603,-37, 37);
    std::cout << formattedString;

    return 0;
}
