#include<string>
#include"position.h"

#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

void kingMoves(int king_loc, uint64_t friendly, std::vector<Move> &moves);
void queenMoves(uint64_t queen_loc, uint64_t friendly, uint64_t all_pieces, std::vector<Move> &moves);
void bishopMoves(uint64_t bishop_loc, uint64_t friendly, uint64_t all_pieces, std::vector<Move> &moves);
void rookMoves(uint64_t rook_loc, uint64_t friendly, uint64_t all_pieces, std::vector<Move> &moves);

namespace Moves {
    std::vector<Move> generateMoves(Position pos);
    void makeMove(Position &pos, Move &move);  
    void unmakeMove(Position &pos, Move move);    
}

#endif 