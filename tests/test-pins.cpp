#include"catch.hpp"
#include"bithacks.h"
/* 
Testing that the move generator can detect absolute pins
*/ 

#include"catch.hpp"
#include"bithacks.h"
#include"position.h" 
#include"moves.h" 
#include<iostream>

TEST_CASE("Pins behave as expected") {
    BitHacks::init(); 
    SECTION("White bishop pins black bishop") {
        Position position; 
        position.setFEN("k7/1b6/2B5/8/8/8/8/8 b - - 0 1");
        position.printPosition();

        std::vector<Move> moves = position.getMoves();
        std::cout << moves.size() << std::endl;
    }
}