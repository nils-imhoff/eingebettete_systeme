#include "../include/Printf.h"
#include <climits>
#include <cstdarg>

static const unsigned int MAX_INT_AS_STRING_LENGTH = decimalLengthOfInt(UINT_MAX) + 1; // +1 for '-' sign
static const unsigned int MAX_INT_AS_HEXSTRING_LENGTH = sizeof(int) * 2;
static const unsigned int MAX_INT_AS_BINARYSTRING_LENGTH = (sizeof(int) * 8);

// calculates the amount of chars necessary to represent an int
int decimalLengthOfInt(unsigned int n)
{
    int i = 0;
    while (n > 0) {
        n = n / 10;
        i++;
    }
    return i;
}

// Copies Array from toCopy to dst; Stops when reaching "end" or when "limit" chars have been copied
char* addStringToString(char* dst, const void* end, char* toCopy, unsigned int limit)
{
    unsigned int loopCounter = 0;
    while (toCopy[loopCounter] != '\0' && dst < end && loopCounter < limit) {
        *dst = toCopy[loopCounter];
        dst++;
        loopCounter++;
    }

    return dst;
}

// writes representative of number in char array.
char* intToBaseString(int num, const int base, const char* c, char* cEnd, const bool twoCom)
{
    *cEnd = '\0';
    unsigned int remainder;
    unsigned int counter = 0;

    unsigned int numUns = static_cast<unsigned int>(num);

    if (numUns == 0) {
        cEnd--;
        *cEnd = '0';
        return cEnd;
    }
    while (numUns != 0 && c < cEnd) {
        cEnd--;
        remainder = numUns % base;
        numUns = numUns / base;
        if (twoCom) {
            remainder = base - 1 - remainder;
            if (counter == 0) {
                if (remainder == 0 && base == 2) {
                    remainder = 1;
                    counter++;
                } else if (remainder == 1 && base == 2) {
                    remainder = 0;
                } else if (remainder == 15 && base == 16) {
                    remainder = 0;
                } else if (remainder != 15 && base == 16) {
                    remainder = remainder + 1;
                    counter++;
                }
            }
        }

        if (remainder <= 9) {

            *cEnd = '0' + remainder;
        } else {
            *cEnd = 'a' + remainder - 10;
        }
    }
    if (twoCom) {
        char* h = cEnd;
        while (*h == '0') {
            h++;
        }
        return h;
    }
    return cEnd;
}

char* Printf(char* dst, const void* end, const char* fmt...)
{

    char* returnPtr;
    va_list args;
    va_start(args, fmt);
    returnPtr = vaPrintf(dst, end, fmt, args);
    va_end(args);
    return returnPtr;
}

char* vaPrintf(char* dst, const void* end, const char* fmt, va_list args)
{
    if (dst == nullptr || end == nullptr || fmt == nullptr || dst >= end) {
        return nullptr;
    }

    char* startBuff = dst;
    bool lastWasPercent = false;
    bool twoCom = false;
    char conversionBuffer[MAX_INT_AS_BINARYSTRING_LENGTH];

    while (dst < end && *fmt != '\0') {
        if (*fmt == '%') {
            if (lastWasPercent) {
                *dst = '%';
                dst++;
                lastWasPercent = false;
            } else {
                lastWasPercent = true;
            }
        } else {
            if (lastWasPercent) {
                switch (*fmt) {
                case 'd': {
                    int i = va_arg(args, int);
                    if (i < 0) {
                        i = i * (-1);
                        *dst = '-';
                        dst++;
                    }
                    char* stringHelper = intToBaseString(i, 10, conversionBuffer, conversionBuffer + MAX_INT_AS_STRING_LENGTH - 1, twoCom);

                    dst = addStringToString(dst, end, stringHelper, MAX_INT_AS_STRING_LENGTH);
                    break;
                }
                case 'u': {
                    int i = va_arg(args, int);
                    char* stringHelper = intToBaseString(i, 10, conversionBuffer, conversionBuffer + MAX_INT_AS_STRING_LENGTH - 1, twoCom);

                    dst = addStringToString(dst, end, stringHelper, MAX_INT_AS_STRING_LENGTH);
                    break;
                }
                case 'c': {
                    int i = va_arg(args, int);
                    *dst = static_cast<char>(i); // char is promoted to int when passed
                    dst++;
                    break;
                }
                case 's': {
                    char* stringHelper = va_arg(args, char*);

                    dst = addStringToString(dst, end, stringHelper, UINT_MAX);
                    break;
                }
                case 'x': {

                    *dst = '0';
                    dst++;
                    if (dst < end) {
                        *dst = 'x';
                        dst++;
                    } else {

                        continue;
                    }

                    int i = va_arg(args, int);
                    if (i < 0) {
                        i = i * (-1);
                        twoCom = true;
                    }

                    char* stringHelper = intToBaseString(i, 16, conversionBuffer, conversionBuffer + MAX_INT_AS_BINARYSTRING_LENGTH - 1, twoCom);

                    dst = addStringToString(dst, end, stringHelper, MAX_INT_AS_HEXSTRING_LENGTH);

                    break;
                }
                case 'b': {

                    *dst = '0';
                    dst++;
                    if (dst < end) {
                        *dst = 'b';
                        dst++;
                    } else {

                        continue;
                    }

                    int i = va_arg(args, int);
                    if (i < 0) {
                        i = i * (-1);
                        twoCom = true;
                    }
                    char* stringHelper = intToBaseString(i, 2, conversionBuffer, conversionBuffer + MAX_INT_AS_BINARYSTRING_LENGTH - 1, twoCom);
                    dst = addStringToString(dst, end, stringHelper, MAX_INT_AS_BINARYSTRING_LENGTH);
                    break;
                }
                default:
                    // return nullptr if unspecified %{character}
                    return nullptr;
                }
                lastWasPercent = false;
                twoCom = false;
            } else {
                *dst = *fmt;
                dst++;
            }
        }

        fmt++;
    }

    *dst = '\0';

    return startBuff;
}
