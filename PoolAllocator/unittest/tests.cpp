#include "catch.hpp"
#include "PoolAllocator.h"

TEST_CASE("test Allocate"){
    SECTION("size smaller than blocksize returns nullptr") {
        CREATE(testAlloc, 2, 4);

        REQUIRE(testAlloc.Allocate(5) == nullptr);
    }

    SECTION("only allocate blockCount amount of blocks with allocation") {
        CREATE(testAlloc, 2, 4);

        testAlloc.Allocate(4);
        testAlloc.Allocate(4);
        REQUIRE(testAlloc.Allocate(4) == nullptr);
    }

    SECTION("only allocate blockCount amount of blocks with mixed allocation and deallocation") {
        CREATE(testAlloc, 2, 4);

        void* testPtr1 = testAlloc.Allocate(4);
        void* testPtr2 = testAlloc.Allocate(4);
        REQUIRE(testAlloc.Allocate(4) == nullptr);
        testAlloc.Deallocate(testPtr1);
        testAlloc.Deallocate(testPtr2);
        
        testAlloc.Allocate(4);
        testAlloc.Allocate(4);
        REQUIRE(testAlloc.Allocate(4) == nullptr);

    }
}

TEST_CASE("test Deallocate") {
    SECTION("deallocate doesnt crash program") {
        CREATE(testAlloc, 2, 8);
        testAlloc.Deallocate(nullptr);
    }    

    SECTION("deallocate doesnt clear data outside of its array") {
        CREATE(testAlloc, 2, 8);
        unsigned int test = 27;
        testAlloc.Deallocate(static_cast<void*>(&test));
        REQUIRE(test == 27);
    }

    SECTION("deallocate only works with pointers on block beginning") {
        CREATE(testAlloc, 2, 4);

        char* testPtr1 = static_cast<char*>(testAlloc.Allocate(4));
        testPtr1[0] = 'a';
        testAlloc.Deallocate(testPtr1-1);

        REQUIRE(testPtr1[0] == 'a');
    }

    SECTION("deallocate clears space after usage") {
        CREATE(testAlloc, 2, 4);

        char* testPtr1 = static_cast<char*>(testAlloc.Allocate(4));
        testPtr1[0] = 'a';
        testAlloc.Deallocate(testPtr1);

        REQUIRE(testPtr1[0] == 0);
    }
}

TEST_CASE("test Available") {
    SECTION("without Allocations") {
        CREATE(testAlloc, 8, 23);

        // should not allocate
        testAlloc.Allocate(24);

        REQUIRE(testAlloc.Available() == 8*23);
    }

    SECTION("when fully allocated") {
        CREATE(testAlloc, 4, 23);
        testAlloc.Allocate(23);
        testAlloc.Allocate(23);
        testAlloc.Allocate(23);
        testAlloc.Allocate(23);

        REQUIRE(testAlloc.Available() == 0);
    }

    SECTION("when partially allocated") {
        CREATE(testAlloc, 4, 23);
        testAlloc.Allocate(20);
        testAlloc.Allocate(15);
        testAlloc.Allocate(10);

        // should not allocate
        testAlloc.Allocate(25);

        REQUIRE(testAlloc.Available() ==  23);
    }
}