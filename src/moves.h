#include<string>
#include"position.h"

#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

void kingMoves(Position &pos, std::vector<Move> &moves);
void queenMoves(Position &pos, std::vector<Move> &moves);
void bishopMoves(Position &pos, std::vector<Move> &moves);
void knightMoves(Position &pos, std::vector<Move> &moves); 
void rookMoves(Position &pos, std::vector<Move> &moves);

uint64_t getPinned(Position &pos);

namespace Moves {
    std::vector<Move> generateMoves(Position &pos);
    void makeMove(Position &pos, Move &move);  
    void unmakeMove(Position &pos, Move move);    
}

#endif 