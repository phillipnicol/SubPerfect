#include<iostream>

#include"bithacks.h"
#include"position.h" 
#include"moves.h"

int main() {
    BitHacks::init();

    Position position; 
    position.setFEN(STARTING_POSITION);
    position.printPosition();

    std::vector<Move> moves = position.getMoves();
    std::cout << moves.size() << std::endl;
}