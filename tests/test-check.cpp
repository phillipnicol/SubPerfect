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
        for(int i = 0; i < moves.size(); ++i) {
            std::cout << int(moves[i].origin) << " " << int(moves[i].destination) << std::endl;
        }
    }
}