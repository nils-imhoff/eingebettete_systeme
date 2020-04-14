#ifndef MULTIDIGIT_H
#define MULTIDIGIT_H

template <typename... Args>
class MultiDigit{
public:
    char printString[sizeof...(Args) * 20 + 1];
    int digits[sizeof...(Args)];

    constexpr MultiDigit(Args...args):
        printString{},
        digits{args...}
    {
        unsigned int nextWrite = 0;
        for(unsigned int row = 0; row < 5; ++row ) {
            for(unsigned int digitNr = 0; digitNr < sizeof...(Args); ++digitNr) {
                printString[nextWrite] = digitChars[digits[digitNr]][row][0];
                ++nextWrite;
                printString[nextWrite] = digitChars[digits[digitNr]][row][1];
                ++nextWrite;
                printString[nextWrite] = digitChars[digits[digitNr]][row][2];
                ++nextWrite;
                printString[nextWrite] = ' ';
                ++nextWrite;
            }
            printString[nextWrite - 1] = '\n';
        }

        printString[nextWrite] = '\0';
    };

    operator const char*() const {
        return this->printString;
    }
private:
    const char digitChars[10][5][3]  = {
        {
            {' ', '-', ' '},
            {'|', ' ', '|'},
            {' ', ' ', ' '},
            {'|', ' ', '|'},
            {' ', '-', ' '}
        },
        {
            {' ', ' ', ' '},
            {' ', ' ', '|'},
            {' ', ' ', ' '},
            {' ', ' ', '|'},
            {' ', ' ', ' '}
        },
        {
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', '-', ' '},
            {'|', ' ', ' '},
            {' ', '-', ' '}
        },
        {
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', '-', ' '}
        },
        {
            {' ', ' ', ' '},
            {'|', ' ', '|'},
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', ' ', ' '}
        },
        {
            {' ', '-', ' '},
            {'|', ' ', ' '},
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', '-', ' '}
        },
        {
            {' ', '-', ' '},
            {'|', ' ', ' '},
            {' ', '-', ' '},
            {'|', ' ', '|'},
            {' ', '-', ' '}
        },
        {
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', ' ', ' '},
            {' ', ' ', '|'},
            {' ', ' ', ' '}
        },
        {
            {' ', '-', ' '},
            {'|', ' ', '|'},
            {' ', '-', ' '},
            {'|', ' ', '|'},
            {' ', '-', ' '}
        },
        {
            {' ', '-', ' '},
            {'|', ' ', '|'},
            {' ', '-', ' '},
            {' ', ' ', '|'},
            {' ', '-', ' '}
        }
    };
};
#endif
