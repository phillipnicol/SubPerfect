#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("KQ6/QQ6/8/8/8/8/6qq/6qk b - - 0 1");
    position.printPosition();

    std::vector<Move> moves = Moves::generateMoves(position);
    std::cout << moves.size() << std::endl;

    Perft::Perft("KQ6/QQ6/8/8/8/8/6qq/6qk b - - 0 1", 4, true);
}