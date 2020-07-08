#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("8/8/8/8/8/8/P7/5K1k w - - 0 1");
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

   Perft::Perft("8/Pp6/8/8/8/8/P7/5K1k w - - 0 1", 2, true); 
}