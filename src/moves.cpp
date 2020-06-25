#include<iostream>
#include"moves.h"

std::vector<Move> Moves::generateMoves(Position pos) {
    std::vector<Move> moves;
    uint64_t all = pos.Pieces[pos.color].all | pos.Pieces[!pos.color].all; 
    uint64_t friendly = pos.Pieces[pos.color].all; 

    if(pos.isinCheck()) {
        //Generate evasions
        kingMoves(_tzcnt_u64(pos.Pieces[pos.color].king), friendly, moves);
        rookMoves(pos.Pieces[pos.color].rook, friendly, all, moves); 
    }
    else {
        //Generate non-evasions 

        kingMoves(_tzcnt_u64(pos.Pieces[pos.color].king), friendly, moves);
        rookMoves(pos.Pieces[pos.color].rook, friendly, all, moves); 
    }

    return moves; 
}

void Moves::makeMove(Position &pos, Move &move) {
    //find which piece is to be moved 
    //place on desired square 
    uint64_t dest = 1ULL << move.destination;  
    uint64_t orig = ~(1ULL << move.origin);

    switch(move.aggressor) {
        case ROOK:
            pos.Pieces[pos.color].rook &= orig;
            pos.Pieces[pos.color].rook |= dest; 
            break;
        case BISHOP:
            pos.Pieces[pos.color].bishop &= orig;
            pos.Pieces[pos.color].bishop |= dest; 
            break;
        case QUEEN:
            pos.Pieces[pos.color].queen &= orig;
            pos.Pieces[pos.color].queen |= dest; 
            break;
        case KING:
            pos.Pieces[pos.color].king &= orig;
            pos.Pieces[pos.color].king |= dest; 
            break; 
    }
    pos.Pieces[pos.color].all &= orig; pos.Pieces[pos.color].all |= dest;

    //Get victim
    if(dest & pos.Pieces[!pos.color].all) { 
        pos.Pieces[!pos.color].all &= ~dest; 
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
}

void Moves::unmakeMove(Position &pos, Move move) {
    //Update game metadata
    if(pos.color == WHITE) {--pos.fullmove_number;}
    pos.color = !pos.color;
    if(move.victim == QUIET & move.aggressor != PAWN) {
        --pos.halfmove_clock;
    }

    uint64_t orig = 1ULL << move.origin; 
    uint64_t dest = 1ULL << move.destination; 
    //Put victim back on board 
    switch(move.victim) {
        case QUIET: break;
        case PAWN:
            break;
        case ROOK: 
            pos.Pieces[!pos.color].rook |= dest; 
            pos.Pieces[!pos.color].all |= dest;
            break;
        case KNIGHT: 
            break;
        case BISHOP:
            break;
        case QUEEN:
            break;
    }

    dest = ~dest; 
    //Put agressor back in correct spot 
    switch(move.aggressor) {
        case PAWN: break;
        case ROOK: 
            pos.Pieces[pos.color].rook |= orig;
            pos.Pieces[pos.color].rook &= dest; 
            break;
        case KNIGHT: break;
        case BISHOP: break;
        case QUEEN: break;
        case KING: 
            pos.Pieces[pos.color].king |= orig; 
            pos.Pieces[pos.color].king &= dest; 
            break;
    }
    pos.Pieces[pos.color].all &= dest; pos.Pieces[pos.color].all |= orig;
}

void kingMoves(int king_loc, uint64_t friendly, std::vector<Move> &moves) {
    uint64_t king_attacks = getKingPseudoLegal(king_loc);
    king_attacks &= ~friendly; 
    Move move;
    move.origin = king_loc;
    move.aggressor = KING; 
    while(king_attacks) {
        move.destination = _tzcnt_u64(king_attacks); 
        moves.push_back(move);

        king_attacks &= (king_attacks - 1); 
    }
}

void rookMoves(uint64_t rook_loc, uint64_t friendly, uint64_t all_pieces, std::vector<Move> &moves) {
    Move move;
    move.aggressor = ROOK; 
    while(rook_loc) {
        move.origin = _tzcnt_u64(rook_loc);
        uint64_t rook_attacks = getRookPseudoLegal(move.origin, all_pieces);
        rook_attacks &= ~friendly; 
        while(rook_attacks) {
            move.destination = _tzcnt_u64(rook_attacks); 
            moves.push_back(move); 
            
            rook_attacks &= (rook_attacks - 1);
        }
        rook_loc &= (rook_loc - 1);
    }
}