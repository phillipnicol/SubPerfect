#include<string>
#include"position.h"

#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

struct GameState {
    char eptarget; 
};

uint64_t getPinned(Position &pos);
void makePromotion(Move currmove, std::vector<Move> &moves);
void enPassantCapture(int targetsq, uint64_t mypawns, Move currmove, std::vector<Move> &moves, bool side);

void kingMoves(Position &pos, std::vector<Move> &moves);
void queenMoves(Position &pos, std::vector<Move> &moves);
void bishopMoves(Position &pos, std::vector<Move> &moves);
void knightMoves(Position &pos, std::vector<Move> &moves); 
void rookMoves(Position &pos, std::vector<Move> &moves);
void pawnMoves(Position &pos, std::vector<Move> &moves);

namespace Moves {
    std::vector<Move> generateMoves(Position &pos);
    GameState makeMove(Position &pos, Move &move);  
    void unmakeMove(Position &pos, Move move, GameState metadata);    
}

#endif 