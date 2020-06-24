#include<vector>
#include<cstdint>

#include"piecetables.h"

#ifndef PIECEMOVES_H_INCLUDED
#define PIECEMOVES_H_INCLUDED

enum PieceType {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, QUIET}; 

//Move struct
//origin and destination between 0 and 63
struct Move {
    char origin, destination;
    int aggressor, victim; 
};

namespace PieceMoves {
    uint64_t getRookPseudoLegal(char square, uint64_t blockers);
    uint64_t getBishopPseudoLegal(char square, uint64_t blockers); 
    uint64_t getQueenPseudoLegal(char square, uint64_t blockers);
    uint64_t getKingPseudoLegal(char square);

    uint64_t findPinnedPieces(Board Friendly, Board Enemy, uint64_t all_pieces);
    uint64_t getPinnedMoves(char square, uint64_t friendly_king, Board Enemy, uint64_t all_pieces);
};

extern std::vector<uint64_t> BishopMasks;
extern std::vector<uint64_t> RookMasks;
extern std::vector<uint64_t> KingMasks; 

extern std::vector<uint64_t> SlidingAttacks;
extern uint32_t RookOffset[64];
extern uint32_t BishopOffset[64]; 


#endif


/*
Code for magic bitboards (unused) 

blockers &= RookMasks[square]; 

uint64_t key = (blockers * ROOK_MAGICS[square]) >> (64 - ROOK_ATTACK_BITS[square]);
return RookMagicBB[square][key]; 

blockers &= BishopMasks[square];

uint64_t key = (blockers * BISHOP_MAGICS[square]) >> (64 - BISHOP_ATTACK_BITS[square]);
return BishopMagicBB[square][key]; 
*/