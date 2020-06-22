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

        std::vector<Move> moves = position.getMoves();
        int bishopmoves = 0; 
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 49) {
                ++bishopmoves;
            }
        }
        REQUIRE(bishopmoves == 1); 
    }
    SECTION("Black bishop pins white bishop") {
        Position position;
        position.setFEN("5K2/8/3B4/8/8/b7/8/8 w - - 0 1");

        int bishopmoves = 0;
        
        std::vector<Move> moves = position.getMoves(); 
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 43) {
                ++bishopmoves;
            }
        }
        REQUIRE(bishopmoves == 4); 
    }
    SECTION("White bishop pins black rook") {
        Position position;
        position.setFEN("7B/8/8/4r3/8/8/8/k7 b - - 0 1");

        int rookmoves = 0;
        std::vector<Move> moves = position.getMoves(); 
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 36) {
                ++rookmoves;
            }
        }
        REQUIRE(rookmoves == 0); 
    }
    SECTION("Black bishop pins white rook") {
        Position position;
        position.setFEN("8/8/8/8/5b2/8/3R4/2K5 w - - 0 1");

        int rookmoves = 0;
        std::vector<Move> moves = position.getMoves(); 
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 11) {
                ++rookmoves;
            }
        }
        REQUIRE(rookmoves == 0);         
    }
    //TODO MORE BISHOP TESTS

    SECTION("White rook pins black rook") {
        Position position;
        position.setFEN("R2r3k/8/8/8/8/8/8/8 b - - 0 1");
        position.printPosition();

        int rookmoves = 0;
        std::vector<Move> moves = position.getMoves();
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 59) {
                ++rookmoves; 
            }
        }
        REQUIRE(rookmoves == 6);
    }
}