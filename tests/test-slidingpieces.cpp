#include"catch.hpp"
#include"bithacks.h"
#include"position.h" 
#include"moves.h" 
#include<iostream>

extern std::vector<std::vector<uint64_t> > RookMagicBB;
extern std::vector<uint64_t> RookMasks;

TEST_CASE("Rook move mechanics are as expected") {
    BitHacks::init(); 
    SECTION("Rook slides freely on an open board") {
        //First we will set a white rook in the corner on a1 
        //Put king on H8 just in case program freaks out without a king 
        Position position; 
        position.setFEN("7K/8/8/8/8/8/8/R7 w - - 0 1");
        position.printPosition(); 
    }
}