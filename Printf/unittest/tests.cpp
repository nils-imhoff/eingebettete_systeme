#include "catch.hpp"
#include "../include/Printf.h"

#include <cstring>

TEST_CASE("Creates correct string", "") {

 SECTION("fmt all specified replacements") {
        char actualString[300];
        char fmt[] = "sint:%d -sint:%d unit:%u unit:%u char:%c string:%s hex:%x -hex:%x bin:%b -bin:%b prozent:%%";
        char expectedString[] = "sint:0 -sint:-23 unit:0 unit:23 char:N string:abc123 hex:0xc8 -hex:0x38 bin:0b101010 -bin:0b10110 prozent:%";
        char* pointerResult = Printf(actualString, actualString + 300 - 1, fmt, 0, -23, 0, 23, 'N', "abc123", 200, -200, 42, -42);

        REQUIRE(strncmp(pointerResult, expectedString, 170) == 0);
    }

    SECTION("creates string without replacements") {
        char actualString[300];
        char stringToPrintf[] = "dies ist ein tests";
        char* result = Printf(actualString, actualString + 300 - 1, stringToPrintf);
        REQUIRE(strncmp(result, stringToPrintf, 300) == 0);
    }

    SECTION("stops at end") {
        char actualString[20];
        char* result = Printf(actualString, actualString + 20 -1, "123456789012345678%d", 395987594);

        REQUIRE(strncmp(result, "1234567890123456783", 21) == 0);
    }
}

TEST_CASE("nullptr on error") {
    SECTION("unspecified %{character}") {
        // %z is not specified

        char* result;
        char actualString[42];
        char fmt[] = "0d:%d 12d:%d %z %d";
        result = Printf(actualString, actualString + 42 - 1, fmt, 0, 1, 2, 3);
        REQUIRE(result == nullptr);
    }

    SECTION("dst nullptr") {
        char actualString[42];
        char* result = Printf(nullptr, actualString + 42 - 1, "%d xyz %s", 23, "abc");

        REQUIRE(result == nullptr);
    }

    SECTION("end nullptr") {
        char actualString[42];
        char* result = Printf(actualString, nullptr, "%d xyz %s", 23, "abc");

        REQUIRE(result == nullptr);
    }

    SECTION("dst > end") {
        char actualString[42];
        char* result = Printf(actualString + 42, actualString, nullptr, 23, "abc");

        REQUIRE(result == nullptr);
    }

    SECTION("fmt nullptr") {
        char actualString[42];
        char* result = Printf(actualString, actualString + 42 - 1, nullptr, 23, "abc");

        REQUIRE(result == nullptr);
    }

    
}
