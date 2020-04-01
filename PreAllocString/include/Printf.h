#ifndef PRINTF_H
#define PRINTF_H

#include <cstdarg>

int decimalLengthOfInt(unsigned int n);
char* addStringToString(char* dst, const void* end, char* toCopy, unsigned int limit);
char* intToBaseString(int num, const int base, const char* c,char* cEnd, const bool twoComp);
char* Printf(char* dst, const void* end , const char* fmt , ...);
char* vaPrintf(char* dst, const void* end, const char* fmt, va_list args);

#endif
