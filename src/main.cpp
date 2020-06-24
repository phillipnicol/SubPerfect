#include<iostream>

#include"moves.h"
#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("RK6/8/8/8/8/8/8/1k5r w - - 0 1");
    position.printPosition();

    std::vector<Move> moves = position.getMoves();
    std::cout << moves.size() << std::endl;

    uint64_t nodes = Perft::Perft("RK6/8/8/8/8/8/8/1k5r w - - 0 1", 5, true);
}