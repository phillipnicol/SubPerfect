#include"catch.hpp"
#include"bithacks.h"
#include<iostream>

extern std::vector<std::vector<uint64_t> > RookMagicBB;
extern std::vector<uint64_t> RookMasks;

TEST_CASE("Rook magic bitboard behaves as expected") {
    BitHacks::init(); 

    uint64_t key;
    //Corners are boxed in if they are surrounded by pieces 
    uint64_t a1blocker = (1ULL << 1) + (1ULL << 8); 
    a1blocker &= RookMasks[0];
    key = (a1blocker*RookMagics[0]) >> (64 - RookAttackBits[0]); 
    REQUIRE(RookMagicBB[0][key] == a1blocker);

    uint64_t h1blocker = (1ULL << 6) + (1ULL << 15); 
    h1blocker &= RookMasks[7];
    key = (h1blocker*RookMagics[7]) >> (64 - RookAttackBits[7]); 
    REQUIRE(RookMagicBB[7][key] == h1blocker);

    uint64_t a8blocker = (1ULL << 48) + (1ULL << 57); 
    a8blocker &= RookMasks[56];
    key = (a8blocker*RookMagics[56]) >> (64 - RookAttackBits[56]); 
    REQUIRE(RookMagicBB[56][key] == a8blocker);

    uint64_t h8blocker = (1ULL << 62) + (1ULL << 55); 
    h8blocker &= RookMasks[63];
    key = (h8blocker*RookMagics[63]) >> (64 - RookAttackBits[63]); 
    REQUIRE(RookMagicBB[63][key] == h8blocker);
}
