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
};

extern std::vector<uint64_t> BishopMasks;
extern std::vector<uint64_t> RookMasks;
extern std::vector<uint64_t> KingMasks; 

extern std::vector<uint64_t> SlidingAttacks;
extern uint32_t RookOffset[64];
extern uint32_t BishopOffset[64]; 

inline uint64_t getRookPseudoLegal(int square, uint64_t blockers) {
    return SlidingAttacks[RookOffset[square] + _pext_u64(blockers, RookMasks[square])];
}

inline uint64_t getBishopPseudoLegal(int square, uint64_t blockers) {
    return SlidingAttacks[BishopOffset[square] + _pext_u64(blockers, BishopMasks[square])];    
}

inline uint64_t getQueenPseudoLegal(int square, uint64_t blockers) {
    return (getRookPseudoLegal(square, blockers) | getBishopPseudoLegal(square, blockers)); 
}

inline uint64_t getKingPseudoLegal(int square) {
    return KingMasks[square]; 
}

inline bool squareAttacked(int square, uint64_t blockers, Board enemy) {
    //Look at rooks 
    if(getRookPseudoLegal(square, blockers) & (enemy.rook | enemy.queen)) {
        return true;
    }
    else if(getBishopPseudoLegal(square, blockers) & (enemy.bishop | enemy.queen)){
        return true;
    }
    else if(getKingPseudoLegal(square) & enemy.king) {
        return true; 
    }
    return false; 
}

inline uint64_t xrayRookAttacks(int square, uint64_t all, uint64_t friendly) {
    uint64_t rook_attacks = getRookPseudoLegal(square, all);
    friendly &= rook_attacks;
    return rook_attacks ^ getRookPseudoLegal(square, all ^ friendly); 
}

inline uint64_t xrayBishopAttacks(int square, uint64_t all, uint64_t friendly) {
    uint64_t bishop_attacks = getBishopPseudoLegal(square, all);
    friendly &= bishop_attacks;
    return bishop_attacks ^ getBishopPseudoLegal(square, all ^ friendly); 
}


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