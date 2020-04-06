#include "../include/PreAllocString.h"
#include "../include/Printf.h"

int main() {
    CREATE(test, 12);
    test+='a';
    test+='b';
    test+='c';
    test+='d';
    

    CREATE(test2, 3);
    test2 += 'e';
    test2 += 'f';
    test2 += 'g';
    test2 += 'h';
    test2 += 'i';
    test2 += 'k';
    test2 += 'l';


    

    CREATE(test3, 10);
    test3.AddFormat("%s", "1234567890");

    return 0;
}

