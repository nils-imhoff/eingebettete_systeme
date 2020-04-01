#include "../include/PreAllocString.h"
#include "../include/Printf.h"
#include <iostream>

int main() {
    CREATE(test, 12);
    test+='a';
    test+='b';
    test+='c';
    test+='d';
    printf("das ist der test: %s\n", static_cast<const char*>(test));

    PreAllocString<3> myPreAllocString;
    myPreAllocString += 'e';
    myPreAllocString += 'f';
    myPreAllocString += 'g';
    myPreAllocString += 'h';
    myPreAllocString += 'i';
    myPreAllocString += 'k';
    myPreAllocString += 'l';


    printf("+=: %s\n", static_cast<const char*>(myPreAllocString));

    PreAllocString<10> myPreAllocString3;
    myPreAllocString3.AddFormat("%s", "1234567890");
    printf("add format: %s\n", static_cast<const char*>(myPreAllocString3));

    return 0;
}

