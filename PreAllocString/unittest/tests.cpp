#include "catch.hpp"
#include <cstring>
#include "../include/PreAllocString.h"
#include "../include/Printf.h"

TEST_CASE("Test implemented Operators") {
    SECTION("testing =operator with char") {
        CREATE(myString, 11);
        char myChar = 'a';
        myString = myChar;

        REQUIRE(myString[0] == 'a');
        REQUIRE(myString[1] == '\0');
    }

    SECTION("testing =operator with const char*") {
        CREATE(myString, 11);
        char myChar = 'z';
        const char* myConstCharPointer = &myChar;
        myString = myChar;

        REQUIRE(myString[0] == 'z');
        REQUIRE(myString[1] == '\0');
    }

    SECTION("testing += operator with char") {
        CREATE(myString, 11);
        myString = 't';
        myString += 'e';
        myString += 's';
        myString += 't';

        REQUIRE(myString[0] == 't');
        REQUIRE(myString[1] == 'e');
        REQUIRE(myString[2] == 's');
        REQUIRE(myString[3] == 't');
        REQUIRE(myString[4] == '\0');
    }

    SECTION("testing += operator with const char*") {
        CREATE(myString, 11);
        const char* testString = "testString";
        myString += testString;

        REQUIRE(strncmp(static_cast<const char*>(myString), testString, 11) == 0);
    }
}

TEST_CASE("Testing member functions") {
    SECTION("Testing GetLength") {
        CREATE(myString, 11);
        myString = 't';
        myString += 'e';
        myString += 's';
        myString += 't';

        REQUIRE(myString.GetLength() == 4);
    }

    SECTION("Testing SizeOf") {
        CREATE(myString, 11);

        REQUIRE(myString.SizeOf() == 11);
    }

    SECTION("Testing Empty") {
        CREATE(myString, 11);
        myString += 'a';

        REQUIRE(myString[0] == 'a');

        myString.Empty();

        REQUIRE(myString[0] == '\0');
        REQUIRE(myString.GetLength() == 0);
    }

    SECTION("Testing Add Whitespace") {
       CREATE(myString, 11);
        myString = 't';
        myString += 'e';
        myString += 's';
        myString.AddWhiteSpace();
        myString += 't';


        REQUIRE(myString[0] == 't');
        REQUIRE(myString[1] == 'e');
        REQUIRE(myString[2] == 's');
        REQUIRE(myString[3] == ' ');
        REQUIRE(myString[4] == 't');
        REQUIRE(myString[5] == '\0');
    }
}

TEST_CASE("Class Respects boundaries of string") {
    SECTION("Using += char") {
        CREATE(myString, 3);
        myString += 'e';
        myString += 'e';
        myString += 'e';

        REQUIRE(myString[2] == '\0');
    }

    SECTION("Using += string" ) {
        CREATE(myString, 10);
        myString += "1234567890";

        REQUIRE(strncmp(static_cast<const char*>(myString), "123456789", 10) == 0);
    }

    SECTION("Using = string" ) {
        CREATE(myString, 10);
        myString = "1234567890";

        REQUIRE(strncmp(static_cast<const char*>(myString), "123456789", 10) == 0);
    }

    SECTION("Using = string AddFormat" ) {
        CREATE(myString, 10);
        myString.AddFormat("%s", "1234567890");
        REQUIRE(strncmp(static_cast<const char*>(myString), "123456789", 10) == 0);
    }
}

