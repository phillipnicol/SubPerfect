#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("Q7/1p6/8/2k5/8/8/8/7K w - - 0 1");
    pos.printPosition(); 

    /*

    std::vector<Move> moves = Moves::generateMoves(pos); 
    
    for(auto move : moves) {
        if(pos.isLegal(move)) {
            GameState gs = Moves::makeMove(pos, move); 
            std::vector<Move> m2s = Moves::generateMoves(pos); 
            int legal = 0;
            for(auto m2 : m2s) {
                if(pos.isLegal(m2)) {
                    ++legal; 
                }
            }
            pos.printPosition(); 
            std::cout << legal << std::endl; 
            Moves::unmakeMove(pos, move, gs); 
        }
    }

    */

    Perft::Perft("Q7/1p6/8/2k5/8/8/8/7K w - - 0 1", 4, true);
}