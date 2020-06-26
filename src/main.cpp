#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("KR6/8/8/8/8/8/8/6rk b - - 0 1");
    position.printPosition();

    std::vector<Move> moves = Moves::generateMoves(position);
    std::cout << moves.size() << std::endl;
    std::cout << position.incheck << std::endl;

    Perft::Perft("rrbqkbrr/8/8/8/8/8/8/RRBQKBRR w - - 0 1", 5, true);
}