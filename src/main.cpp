#include<iostream>

#include"bithacks.h"
#include"board.h"
#include"moves.h"
#include"position.h" 

int main() {
    BitHacks::init();

    Position position; 
    position.setFEN("Q7/8/8/8/8/8/8/8 w - - 0 1");
    position.printPosition();

    std::vector<Move> moves = position.getMoves();
    std::cout << moves.size() << std::endl;
    for(auto move : moves) {
        std::cout << int(move.origin) << " " << int(move.destination) << std::endl;
    }
}