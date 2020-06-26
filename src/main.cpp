#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("KQ6/8/8/8/8/8/8/6qk b - - 0 1");
    position.printPosition();

    std::vector<Move> moves = Moves::generateMoves(position);
    std::cout << moves.size() << std::endl;
    std::cout << position.incheck << std::endl;

     Perft::Perft("KQ6/8/8/8/8/8/8/6qk b - - 0 1", 2, true);
}