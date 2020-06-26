#include<iostream>
#include<vector>
#include<cstdint> 
#include"piecemoves.h"

CheckType PieceMoves::getCheckData(int kingsq, Board friendly, Board enemy) {
    int nchecks = 0; 
    uint64_t safety_map = 0ULL; 
    uint64_t blockers = friendly.all | enemy.all; 

    uint64_t danger = getRookPseudoLegal(kingsq, blockers) & (enemy.rook | enemy.queen);
    if(danger) {
        nchecks += _popcnt64(danger);
        int attacksq = _tzcnt_u64(danger);
        safety_map = getRookPseudoLegal(kingsq, blockers) & getRookPseudoLegal(attacksq, blockers);
        safety_map |= (1ULL << attacksq);     
    }
    danger = getBishopPseudoLegal(kingsq, blockers) & (enemy.bishop | enemy.queen);
    if(danger) {
        nchecks += _popcnt64(danger);
        int attacksq = _tzcnt_u64(danger);
        safety_map = getBishopPseudoLegal(kingsq, blockers) & getBishopPseudoLegal(attacksq, blockers); 
        safety_map |= (1ULL << attacksq);   
    }
    danger = getKnightPseudoLegal(kingsq) & enemy.knight;
    if(danger) {
        nchecks += _popcnt64(danger);
        int attacksq = _tzcnt_u64(danger);
        safety_map = 1ULL << attacksq; 
    }

    CheckType checkdata;
    checkdata.nchecks = nchecks; checkdata.safety_map = safety_map; 
    return checkdata; 
}
