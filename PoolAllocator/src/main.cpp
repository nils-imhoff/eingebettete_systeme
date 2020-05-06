#include "PoolAllocator.h"
int main() {
  CREATE(testAlloc, 2, 4);

  char* testPtr1 = static_cast<char*>(testAlloc.Allocate(4));
  testPtr1[0] = 'a';
  testAlloc.Deallocate(testPtr1);

  return 0;
}
