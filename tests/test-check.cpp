#include"catch.hpp"
#include"bithacks.h"
/* 

*/ 

#include"catch.hpp"
#include"bithacks.h"
#include"position.h" 
#include"moves.h" 
#include<iostream>

TEST_CASE("Checks behave as expected") {
    BitHacks::init(); 
    SECTION("White rook checks black king") {
        Position position;
        position.setFEN("R6k/8/8/8/8/8/8/8 b - - 0 1");
        position.printPosition();

        std::vector<Move> moves = position.getMoves(); 
        REQUIRE(moves.size() == 2);
        REQUIRE(position.incheck == 1); 
    }
    SECTION("King can't move along the rook ray") {
        Position position;
        position.setFEN("8/7K/7r/8/8/8/8/8 w - - 0 1");
        position.printPosition(); 

        std::vector<Move> moves = position.getMoves(); 
        for(auto move : moves) {
            std::cout << int(move.origin) << " " << int(move.destination) << std::endl;
        }
        REQUIRE(moves.size() == 3); 
        REQUIRE(position.incheck == 1);
    }
}