#include "../include/Printf.h"

#include <iostream>
static const unsigned int STRING_LENGTH = 300;

int main() {
    char print[STRING_LENGTH];
    char* returnString = Printf(print, print + STRING_LENGTH, "int: %d\nunsginedint: %u\ncharacter: %c\nstring: %s\nhexaminus: %x\nhexaplus: %x\nbinaryminus: %b\nbinaryplus: %b\nprozentzeichen: %%\n", -94, 3, 'n', "test", -2048, 4605,-42, 42);
    std::cout << returnString;

    return 0;
}
