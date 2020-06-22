#include<iostream>
#include<vector>
#include"position.h"
#include"moves.h"
#include"bithacks.h"


uint64_t Moves::getRookPseudoLegal(char square, uint64_t blockers) {
    blockers &= RookMasks[square]; 

    uint64_t key = (blockers * RookMagics[square]) >> (64 - RookAttackBits[square]);
    return RookMagicBB[square][key]; 
}

uint64_t Moves::getBishopPseudoLegal(char square, uint64_t blockers) {
    blockers &= BishopMasks[square];

    uint64_t key = (blockers * BishopMagics[square]) >> (64 - BishopAttackBits[square]);
    return BishopMagicBB[square][key]; 
}

uint64_t Moves::getQueenPseudoLegal(char square, uint64_t blockers) {
    return (Moves::getBishopPseudoLegal(square, blockers) | Moves::getRookPseudoLegal(square, blockers));
}