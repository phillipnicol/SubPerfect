#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("7k/P7/8/8/8/8/8/7K w - - 0 1");
    pos.printPosition(); 

    int count = 0;

    std::vector<Move> moves = Moves::generateMoves(pos);
    for(auto move : moves) {
        Moves::makeMove(pos, move);
        std::vector<Move> deep = Moves::generateMoves(pos);
        for(auto m2 : deep) {
            if(pos.isLegal(m2)) {
            Moves::makeMove(pos, m2);
            pos.printPosition();
            ++count;
            Moves::unmakeMove(pos, m2);
            }
        }
        Moves::unmakeMove(pos, move); 
    }

    std::cout << count << std::endl;
    //Perft::Perft("7k/P7/8/8/8/8/8/7K w - - 0 1", 2, true);
}