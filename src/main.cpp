#include"perft.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN("8/8/8/3K4/8/4k3/8/8 w - - 0 1");
    position.printPosition();

    std::vector<Move> moves = Moves::generateMoves(position);
    std::cout << moves.size() << std::endl;

    for(auto move : moves) {
        if(position.isLegal(move)) {
            std::cout << int(move.origin) << " " << int(move.destination) << std::endl;            
        }
    }

    Perft::Perft("8/8/8/3K4/8/4k3/8/8 w - - 0 1", 4, true);
}