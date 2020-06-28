#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("8/8/8/Pp6/8/8/8/3k3K w - b6 0 1");
    pos.printPosition(); 

    std::vector<Move> moves = Moves::generateMoves(pos);
    std::cout << moves.size() << std::endl; 

    //Perft::Perft("8/8/8/Pp6/8/8/8/3k3K w - b6 0 1", 6, true);
}