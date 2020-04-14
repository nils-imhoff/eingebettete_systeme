#include "catch.hpp"
#include "7Segment.h"

#include <cstring>

TEST_CASE("Test Single Digit") {
    SECTION("Digit 0") {
        const char zeroRepresent[] = " - \n| |\n   \n| |\n - \n";
        constexpr MultiDigit md{0};
        REQUIRE(strncmp(static_cast<const char*>(md),zeroRepresent,22) == 0);
    }

    SECTION("Digit 1") {
        const char oneRepresent[] = "   \n  |\n   \n  |\n   \n";
        constexpr MultiDigit md{1};
        REQUIRE(strncmp(static_cast<const char*>(md),oneRepresent,22) == 0);
    }

    SECTION("Digit 2") {
        const char twoRepresent[] = " - \n  |\n - \n|  \n - \n";
        constexpr MultiDigit md{2};
        REQUIRE(strncmp(static_cast<const char*>(md),twoRepresent,22) == 0);
    }

    SECTION("Digit 3") {
        const char threeRepresent[] = " - \n  |\n - \n  |\n - \n";
        constexpr MultiDigit md{3};
        REQUIRE(strncmp(static_cast<const char*>(md),threeRepresent,22) == 0);
    }

    SECTION("Digit 4") {
        const char fourRepresent[] = "   \n| |\n - \n  |\n   \n";
        constexpr MultiDigit md{4};
        REQUIRE(strncmp(static_cast<const char*>(md),fourRepresent,22) == 0);
    }

    SECTION("Digit 5") {
        const char fiveRepresent[] = " - \n|  \n - \n  |\n - \n";
        constexpr MultiDigit md{5};
        REQUIRE(strncmp(static_cast<const char*>(md),fiveRepresent,22) == 0);
    }

    SECTION("Digit 6") {
        const char sixRepresent[] = " - \n|  \n - \n| |\n - \n";
        constexpr MultiDigit md{6};
        REQUIRE(strncmp(static_cast<const char*>(md),sixRepresent,22) == 0);
    }

    SECTION("Digit 7") {
        const char sevenRepresent[] = " - \n  |\n   \n  |\n   \n";
        constexpr MultiDigit md{7};
        REQUIRE(strncmp(static_cast<const char*>(md),sevenRepresent,22) == 0);
    }

    SECTION("Digit 8") {
        const char eightRepresent[] = " - \n| |\n - \n| |\n - \n";
        constexpr MultiDigit md{8};
        REQUIRE(strncmp(static_cast<const char*>(md),eightRepresent,22) == 0);
    }

    SECTION("Digit 9") {
        const char nineRepresent[] = " - \n| |\n - \n  |\n - \n";
        constexpr MultiDigit md{9};
        REQUIRE(strncmp(static_cast<const char*>(md),nineRepresent,22) == 0);
    }
}

TEST_CASE("Multiple Digits") {
    SECTION("all possible digits concatenated") {
        constexpr MultiDigit md{5,4,6,3,7,2,8,1,9,0};
        const char expectedRepresent[] = " -       -   -   -   -   -       -   - \n|   | | |     |   |   | | |   | | | | |\n -   -   -   -       -   -       -     \n  |   | | |   |   | |   | |   |   | | |\n -       -   -       -   -       -   - \n";

        REQUIRE(strncmp(static_cast<const char*>(md), expectedRepresent, 186) == 0);
    }
}
