#include "7Segment.h"
#include <stdio.h>

int main() {
    constexpr MultiDigit md{0,1,2,3,4,5,6,7,8,9};
    printf("mein string: \n%s", static_cast<const char*>(md));
    return 0;
}
