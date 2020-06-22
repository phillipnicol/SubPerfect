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
        Position position; 
        position.setFEN("8/8/8/8/8/8/8/R7 w - - 0 1");

        std::vector<char> destinations;

        std::vector<Move> moves = position.getMoves(); 
        REQUIRE(moves.size() == 14); 

        for(int i = 0; i < moves.size(); ++i) {
            destinations.push_back(moves[i].destination);
        }
        std::sort(destinations.begin(), destinations.end());
        const int target[14] = {1,2,3,4,5,6,7,8,16,24,32,40,48,56};
        for(int i = 0; i < 14; ++i) {
            REQUIRE(moves[i].destination == target[i]);
        }

        //Now we will check the center. Rook on e4 
        position.setFEN("8/8/8/8/4R3/8/8/8 w - - 0 1");

        moves = position.getMoves(); 
        
        destinations.clear(); 
        REQUIRE(moves.size() == 14); 
        for(int i = 0; i < moves.size(); ++i) {
            destinations.push_back(moves[i].destination); 
        }
        std::sort(destinations.begin(), destinations.end()); 
        const int target2[14] = {4,12,20,24,25,26,27,29,30,31,36,44,52,60}; 
        for(int i = 0; i < 14; ++i) {
            REQUIRE(moves[i].destination == target2[i]); 
        }  
    }

    SECTION("Rook can not capture a piece with its own color") {
        Position position; 
        //position.setFEN("8/8/8/8/4R3/8/8/8 w - - 0 1");
        position.setFEN("8/8/8/8/8/8/1r4b1/8 b - - 0 1"); 
        position.printPosition(); 

        std::vector<Move> moves = position.getMoves(); 

        std::cout << moves.size() << std::endl;
        for(int i = 0; i < moves.size(); ++i) {
            std::cout << int(moves[i].origin) << " " << int(moves[i].destination) << std::endl;
        }
    }
}