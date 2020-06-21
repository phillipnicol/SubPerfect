#include"catch.hpp"
#include"bithacks.h"
#include<iostream>

extern std::vector<std::vector<uint64_t> > RookMagicBB;
extern std::vector<uint64_t> RookMasks;

//This will test the magic bitboard construction 
TEST_CASE("Function getBlockers works as expected") {
    uint64_t BB = getBlocker(0, RookMasks[35]);
    BitHacks::printBitBoard(BB);
    REQUIRE(BB == 0ULL);

    std::cout << "\n \n"; 

    BB = getBlocker(1024, RookMasks[35]); 
    BitHacks::printBitBoard(BB);
}


//Test 1 will have just a few blockers
uint64_t test1 = (1ULL << 10) + (1ULL << 14) + (1ULL << 34) + (1ULL << 45);
uint64_t test2 = 0ULL;
uint64_t test3 = 0ULL; 

TEST_CASE("Rook magic bitboard is correct") {
    BitHacks::init(); 
}
