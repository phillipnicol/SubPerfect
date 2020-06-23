#include<iostream>
#include"moves.h"

Position Moves::makeMove(Position &pos, Move move) {
    Position oldpos = pos;

    //find which piece is to be moved 
    //place on desired square 
    int aggressor = move.aggressor;
    uint64_t dest = 1ULL << move.destination;  

    switch(aggressor) {
        case ROOK:
            pos.Pieces[pos.color].rook &= ~(1ULL << move.origin); 
            pos.Pieces[pos.color].rook |= dest; 
            break;
        case BISHOP:
            pos.Pieces[pos.color].bishop &= ~(1ULL << move.origin);
            pos.Pieces[pos.color].bishop |= dest; 
            break;
        case QUEEN:
            pos.Pieces[pos.color].queen &= ~(1ULL << move.origin);
            pos.Pieces[pos.color].queen |= dest; 
            break;
        case KING:
            pos.Pieces[pos.color].king &= ~(1ULL << move.origin);
            pos.Pieces[pos.color].king |= dest; 
            break; 
    }
    pos.Pieces[pos.color].all &= ~(1ULL << move.origin); 


    //Get victim
    if((dest & pos.Pieces[!pos.color].all) != 0) {
        uint64_t dest = (1ULL << move.destination); 
        if((dest & pos.Pieces[!pos.color].pawn) != 0) {
            move.victim = PAWN; 
            pos.Pieces[!pos.color].pawn &= ~dest; 
        }
        else if((dest & pos.Pieces[!pos.color].rook) != 0) {
            move.victim = ROOK; 
            pos.Pieces[!pos.color].rook &= ~dest; 
        }
        else if((dest & pos.Pieces[!pos.color].knight) != 0) {
            move.victim = KNIGHT; 
            pos.Pieces[!pos.color].knight &= ~dest; 
        }
        else if((dest & pos.Pieces[!pos.color].bishop) != 0) {
            move.victim = BISHOP; 
            pos.Pieces[!pos.color].bishop &= ~dest; 
        }
        else {
            move.victim = QUEEN; 
            pos.Pieces[!pos.color].queen &= ~dest; 
        }
    }
    else {
        move.victim = QUIET; 
    }

    //update game metadata 
    if(pos.color == BLACK) {++pos.fullmove_number;} //update move number
    pos.color = !pos.color; //switch color
    if(move.victim != QUIET | move.aggressor == PAWN) {
        pos.halfmove_clock = 0; 
    } //for 50 move draw
    pos.incheck = false; 
    //***TODO SPECIAL MOVE INFO 

    return oldpos; 
}