
/* 
The point of this test is to ensure that the basic movements for each piece 
is correct. 
*/

#include"catch.hpp"
#include"bithacks.h"
#include"board.h"
#include"moves.h" 
#include"position.h" 
#include<iostream>

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
        const char target[14] = {1,2,3,4,5,6,7,8,16,24,32,40,48,56};
        for(int i = 0; i < 14; ++i) {
            REQUIRE(destinations[i] == target[i]);
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
        const char target2[14] = {4,12,20,24,25,26,27,29,30,31,36,44,52,60}; 
        for(int i = 0; i < 14; ++i) {
            REQUIRE(destinations[i] == target2[i]); 
        }  
    }

    SECTION("Rook can not capture a piece with of its own color") {
        Position position; 
        position.setFEN("8/1n6/8/8/4p3/8/1r4b1/8 b - - 0 1"); 

        std::vector<Move> moves = position.getMoves(); 

        REQUIRE(moves.size() == 14); 
        const char target[10] = {1,8,10,11,12,13,17,25,33,41}; 
        std::vector<char> destinations; 
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 9) {
                destinations.push_back(moves[i].destination);
            }
        }
        std::sort(destinations.begin(), destinations.end()); 
        for(int i = 0; i < destinations.size(); ++i) {
            REQUIRE(destinations[i] == target[i]);
        }
    }

    SECTION("Rook can capture a piece of the opposite color") {
        Position position; 
        position.setFEN("8/6R1/6n1/8/8/8/8/8 w - - 0 1");

        std::vector<Move> moves = position.getMoves(); 
        std::vector<char> destinations; 
        for(int i = 0; i < moves.size(); ++i) {
            destinations.push_back(moves[i].destination); 
        }
        std::sort(destinations.begin(), destinations.end());
        REQUIRE(moves.size() == 9);
        const char target[9] = {46,48,49,50,51,52,53,55,62}; 
        for(int i = 0; i < moves.size(); ++i) {
            REQUIRE(destinations[i] == target[i]);
        }
    }
}

TEST_CASE("Bishop movement is as expected") {
    SECTION("Bishop moves freely on an open board") {
        //First we will set a white bishop in the corner on a1 
        Position position; 
        position.setFEN("8/8/8/8/8/8/8/B7 w - - 0 1");

        std::vector<Move> moves = position.getMoves(); 
        REQUIRE(moves[0].origin == 0);
        REQUIRE(moves.size() == 7); 
        const char target[7] = {9,18,27,36,45,54,63};
        std::vector<char> destinations;
        for(int i = 0; i < moves.size(); ++i) {
            destinations.push_back(moves[i].destination);
        }
        std::sort(destinations.begin(), destinations.end()); 
        for(int i = 0; i < moves.size(); ++i) {
            REQUIRE(destinations[i] == target[i]);
        }

        //Now we will drop one on e4 
        position.setFEN("8/8/8/8/4B3/8/8/8 w - - 0 1");

        moves = position.getMoves(); 
        destinations.clear(); 

        std::cout << moves.size() << std::endl;
        REQUIRE(moves.size() == 13);
        for(int i = 0; i < moves.size(); ++i) {
            std::cout << int(moves[i].origin) << " " << int(moves[i].destination) << std::endl;
            destinations.push_back(moves[i].destination); 
        }
        const char target2[13] = {1,7,10,14,19,21,35,37,42,46,49,55,56};
        std::sort(destinations.begin(), destinations.end()); 
        for(int i = 0; i < destinations.size(); ++i) {
            REQUIRE(destinations[i] == target2[i]); 
        }
    }
    SECTION("Bishop will not capture pieces on its own team.") {
        Position position;
        position.setFEN("8/5B2/8/8/8/1P6/8/8 w - - 0 1");

        std::vector<Move> moves = position.getMoves(); 
        std::vector<char> destinations;
        REQUIRE(moves.size() == 7); 
        for(int i = 0; i < moves.size(); ++i) {
            if(moves[i].origin == 53) {
                destinations.push_back(moves[i].destination);
            }
        }

        const char target[7] = {26,35,39,44,46,60,62};
        std::sort(destinations.begin(), destinations.end());
        for(int i = 0; i < destinations.size(); ++i) {
            REQUIRE(destinations[i] == target[i]); 
        }
    }
    SECTION("Bishop can capture pieces on the opposite side") {
        Position position;
        position.setFEN("8/8/8/2n5/1b6/8/8/8 b - - 0 1");

        std::vector<Move> moves = position.getMoves(); 
        std::vector<char> destinations;
        REQUIRE(moves.size() == 5); 
        for(int i = 0; i < moves.size(); ++i) {
            destinations.push_back(moves[i].destination); 
        }

        const char target[7] = {4,11,16,18,32};
        std::sort(destinations.begin(), destinations.end());
        for(int i = 0; i < destinations.size(); ++i) {
            REQUIRE(destinations[i] == target[i]); 
        }
    }
}

TEST_CASE("Queen movement is as expected") {
    SECTION("Queen slides freely on an open board") {
        //Let's try H1
        Position position;
        position.setFEN("8/8/8/8/8/8/8/7Q w - - 0 1");

        std::vector<Move> moves = position.getMoves();
        REQUIRE(moves.size() == 21); 
        for(int i = 0; i < moves.size(); ++i) {
            std::cout << int(moves[i].origin) << " " << int(moves[i].destination) << std::endl;
        }

        //Now let's try f6
        position.setFEN("8/8/5q2/8/8/8/8/8 b - - 0 1");

        moves = position.getMoves();

        REQUIRE(moves.size() == 25); 
    }
}