#include<vector>
#include"position.h"
#include"moves.h"
#include"bithacks.h"


uint64_t Moves::getRookPseudoLegal(char square, uint64_t blockers) {
    blockers &= RookMasks[square]; 

    uint64_t key = (blockers * RookMagics[square]) >> (64 - RookAttackBits[square]);
    return RookMagicBB[square][key]; 
}