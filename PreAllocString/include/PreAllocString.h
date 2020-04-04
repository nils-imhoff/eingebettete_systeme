#ifndef PREALLOCSTRING_H
#define PREALLOCSTRING_H

#include "../include/Printf.h"

#include <cstdarg>
#include <cstddef>

#define CREATE(varName, size) \
    PreAllocString<size> varName

template <size_t Stringsize>
class PreAllocString {
public:
    operator const char*() const;
    operator const void*() const;

    const char& operator[](const int idx);

    size_t GetLength() const;

    constexpr size_t SizeOf();

    void Empty();

    PreAllocString& operator=(char rhs);
    PreAllocString& operator=(const char* rhs);
    PreAllocString& operator=(char* const rhs);

    PreAllocString& operator+=(char rhs);
    PreAllocString& operator+=(char const* rhs);

    void AddFormat(const char* format, ...);
    void AddWhiteSpace();

private:
    char myString[Stringsize] { '\0' };
};

template <size_t Stringsize>
PreAllocString<Stringsize>::operator const char*() const
{
    return myString;
};

template <size_t Stringsize>
PreAllocString<Stringsize>::operator const void*() const
{
    return static_cast<const void*>(myString);
};

template <size_t Stringsize>
const char& PreAllocString<Stringsize>::operator[](const int idx)
{
    if (static_cast<unsigned int>(idx) < Stringsize && idx >= 0) {
        return myString[idx];
    }

    return myString[0];
};

template <size_t Stringsize>
size_t PreAllocString<Stringsize>::GetLength() const
{
    size_t len = 0;

    while (myString[len] != 0 && len < Stringsize) {
        ++len;
    }

    return len;
};

template <size_t Stringsize>
constexpr size_t PreAllocString<Stringsize>::SizeOf()
{
    return Stringsize;
}

template <size_t Stringsize>
void PreAllocString<Stringsize>::Empty()
{
    myString[0] = '\0';
}

template <size_t Stringsize>
PreAllocString<Stringsize>& PreAllocString<Stringsize>::operator=(char rhs)
{
    if (Stringsize >= 2) {
        myString[0] = rhs;
        myString[1] = '\0';
    }

    return *this;
};

template <size_t Stringsize>
PreAllocString<Stringsize>& PreAllocString<Stringsize>::operator=(const char* rhs)
{
    unsigned int i = 0;

    while (rhs[i] != '\0' && i < Stringsize - 1) {
        myString[i] = rhs[i];
        ++i;
    }

    myString[i] = '\0';

    return *this;
};

template <size_t Stringsize>
PreAllocString<Stringsize>& PreAllocString<Stringsize>::operator=(char* const rhs)
{
    this += static_cast<const char*>(rhs);
};

template <size_t Stringsize>
PreAllocString<Stringsize>& PreAllocString<Stringsize>::operator+=(char rhs)
{
    size_t iMyString = GetLength();

    if (iMyString < Stringsize - 1) {
        myString[iMyString] = rhs;
        ++iMyString;
        myString[iMyString] = '\0';
    }
    return *this;
};

template <size_t Stringsize>
PreAllocString<Stringsize>& PreAllocString<Stringsize>::operator+=(char const* rhs)
{
    size_t i = GetLength();

    while (rhs[i] != '\0' && i < Stringsize - 1) {
        myString[i] = rhs[i];
        ++i;
    }

    myString[i] = '\0';

    return *this;
};

template <size_t Stringsize>
    void PreAllocString<Stringsize>::AddFormat(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    size_t endOfString = GetLength();

    vaPrintf(&myString[endOfString], myString + Stringsize - 1, format, args);
    va_end(args);
};

template <size_t Stringsize>
void PreAllocString<Stringsize>::AddWhiteSpace()
{
    *this += ' ';
};

#endif
