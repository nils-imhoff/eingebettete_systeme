#include "catch.hpp"
#include <cstring>
#include "../include/PreAllocString.h"
#include "../include/Printf.h"

TEST_CASE("Test implemented Operators") {
    SECTION("testing =operator with char") {
        PreAllocString<11> myPreAllocString;
        char myChar = 'a';
        myPreAllocString = myChar;

        REQUIRE(myPreAllocString[0] == 'a');
        REQUIRE(myPreAllocString[1] == '\0');
    }

    SECTION("testing =operator with const char*") {
        PreAllocString<11> myPreAllocString;
        char myChar = 'z';
        const char* myConstCharPointer = &myChar;
        myPreAllocString = myChar;

        REQUIRE(myPreAllocString[0] == 'z');
        REQUIRE(myPreAllocString[1] == '\0');
    }

    SECTION("testing += operator with char") {
        PreAllocString<11> myPreAllocString;
        myPreAllocString = 't';
        myPreAllocString += 'e';
        myPreAllocString += 's';
        myPreAllocString += 't';

        REQUIRE(myPreAllocString[0] == 't');
        REQUIRE(myPreAllocString[1] == 'e');
        REQUIRE(myPreAllocString[2] == 's');
        REQUIRE(myPreAllocString[3] == 't');
        REQUIRE(myPreAllocString[4] == '\0');
    }

    SECTION("testing += operator with const char*") {
        PreAllocString<11> myPreAllocString;
        const char* testString = "testString";
        myPreAllocString += testString;

        REQUIRE(strncmp(static_cast<const char*>(myPreAllocString), testString, 11) == 0);
    }
}

TEST_CASE("Testing member functions") {
    SECTION("Testing GetLength") {
        PreAllocString<11> myPreAllocString;
        myPreAllocString = 't';
        myPreAllocString += 'e';
        myPreAllocString += 's';
        myPreAllocString += 't';

        REQUIRE(myPreAllocString.GetLength() == 4);
    }

    SECTION("Testing SizeOf") {
        PreAllocString<11> myPreAllocString;

        REQUIRE(myPreAllocString.SizeOf() == 11);
    }

    SECTION("Testing Empty") {
        PreAllocString<11> myPreAllocString;
        myPreAllocString += 'a';

        REQUIRE(myPreAllocString[0] == 'a');

        myPreAllocString.Empty();

        REQUIRE(myPreAllocString[0] == '\0');
        REQUIRE(myPreAllocString.GetLength() == 0);
    }

    SECTION("Testing Add Whitespace") {
        PreAllocString<11> myPreAllocString;
        myPreAllocString = 't';
        myPreAllocString += 'e';
        myPreAllocString += 's';
        myPreAllocString.AddWhiteSpace();
        myPreAllocString += 't';


        REQUIRE(myPreAllocString[0] == 't');
        REQUIRE(myPreAllocString[1] == 'e');
        REQUIRE(myPreAllocString[2] == 's');
        REQUIRE(myPreAllocString[3] == ' ');
        REQUIRE(myPreAllocString[4] == 't');
        REQUIRE(myPreAllocString[5] == '\0');
    }
}

TEST_CASE("Class Respects boundaries of string") {
    SECTION("Using += char") {
        PreAllocString<3> myPreAllocString;
        myPreAllocString += 'e';
        myPreAllocString += 'e';
        myPreAllocString += 'e';

        REQUIRE(myPreAllocString[2] == '\0');
    }

    SECTION("Using += string" ) {
        PreAllocString<10> myPreAllocString;
        myPreAllocString += "1234567890";

        REQUIRE(strncmp(static_cast<const char*>(myPreAllocString), "123456789", 10) == 0);
    }

    SECTION("Using = string" ) {
        PreAllocString<10> myPreAllocString;
        myPreAllocString = "1234567890";

        REQUIRE(strncmp(static_cast<const char*>(myPreAllocString), "123456789", 10) == 0);
    }

    SECTION("Using = string AddFormat" ) {
        PreAllocString<10> myPreAllocString;
        myPreAllocString.AddFormat("%s", "1234567890");
        REQUIRE(strncmp(static_cast<const char*>(myPreAllocString), "123456789", 10) == 0);
    }
}

