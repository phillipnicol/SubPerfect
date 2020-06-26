#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w - - 0 1");
    position.printPosition();

    std::vector<Move> moves = Moves::generateMoves(position);

    Perft::Perft("rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w - - 0 1", 5, true);
}