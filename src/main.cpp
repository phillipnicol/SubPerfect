#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("KR5r/8/4R3/3r4/8/8/8/kr5R w - - 0 1");
    position.printPosition();

    //std::vector<Move> moves = Moves::generateMoves(position);

    Perft::Perft("KR5r/8/4R3/3r4/8/8/8/kr5R w - - 0 1", 4, true);
}