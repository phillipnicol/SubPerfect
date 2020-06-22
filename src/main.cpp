#include<iostream>

#include"bithacks.h"
#include"position.h" 
#include"moves.h"

int main() {
    BitHacks::init();

    Position position; 
    position.setFEN("k7/1b6/2B5/8/8/8/8/8 b - - 0 1");
    position.printPosition();

    std::vector<Move> moves = position.getMoves();
    std::cout << moves.size() << std::endl;
}