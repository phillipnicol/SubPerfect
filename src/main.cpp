#include<iostream>

#include"moves.h"
#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("Q7/8/8/8/8/8/8/q7 w - - 0 1");
    position.printPosition();

    uint64_t nodes = Perft::Perft(position, 6); 
    std::cout << nodes << std::endl;
}