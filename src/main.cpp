#include<iostream>

#include"bithacks.h"
#include"position.h" 
#include"moves.h"

int main() {
    BitHacks::init();

    Position position; 
    position.setFEN("8/8/5R2/p1k5/1p2b3/1P6/1P6/K7 w - - 0 39");
    position.printPosition();

    std::vector<Move> moves = position.getMoves();
    std::cout << moves.size() << std::endl;
}