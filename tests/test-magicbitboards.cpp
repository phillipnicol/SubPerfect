#include"catch.hpp"
#include"bithacks.h"
#include<iostream>

extern std::vector<std::vector<uint64_t> > RookMagicBB;

TEST_CASE("Rook magic bitboard is correct") {
    BitHacks::init(); 
    BitHacks::printBitBoard(RookMagicBB[0][0]);
}
