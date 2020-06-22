#include<iostream>
#include<vector>
#include<cstdint> 
#include"position.h"
#include"moves.h"
#include"bithacks.h"
#include"board.h" 


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

uint64_t Moves::findPinnedPieces(Board Friendly, Board Enemy, uint64_t all_pieces) {
    uint64_t pinned = 0ULL;
    //If no king, simply return nothing
    if(Friendly.king == 0ULL) {return pinned;}

    //First we get moves from the opponent's sliding pieces 
    std::vector<char> rooks = BitHacks::serialize(Enemy.rook);
    std::vector<char> bishops = BitHacks::serialize(Enemy.bishop);
    std::vector<char> queens = BitHacks::serialize(Enemy.queen); 
    //diagonal
    uint64_t enemy_diagonals = 0ULL;
    for(int i = 0; i < bishops.size(); ++i) {
        enemy_diagonals |= Moves::getBishopPseudoLegal(bishops[i], all_pieces);
    }
    for(int i = 0; i < queens.size(); ++i) {
        enemy_diagonals |= Moves::getBishopPseudoLegal(queens[i], all_pieces);
    }
    enemy_diagonals &= ~Enemy.all;

    //straights
    uint64_t enemy_straights = 0ULL;
    for(int i = 0; i < rooks.size(); ++i) {
        enemy_straights |= Moves::getRookPseudoLegal(rooks[i], all_pieces);
    }
    for(int i = 0; i < queens.size(); ++i) {
        enemy_straights |= Moves::getRookPseudoLegal(rooks[i], all_pieces); 
    }
    enemy_straights &= ~Enemy.all; 

    //Now get sliding attacks from the king
    char king_location = __builtin_ctzl(Friendly.king);
    uint64_t kingrays_diagonal = Moves::getBishopPseudoLegal(king_location, all_pieces);
    uint64_t kingrays_straight = Moves::getRookPseudoLegal(king_location, all_pieces);  

    //Now we combine this information 
    pinned = (kingrays_diagonal & enemy_diagonals) | (kingrays_straight & enemy_straights);
    BitHacks::printBitBoard(pinned);
    return pinned;
}

//Maybe redundant given other calculations
//Relying on the fact that 
uint64_t Moves::getPinnedMoves(char square, uint64_t friendly_king, Board Enemy, uint64_t all_pieces) {
    //Remove pinned piece from the board 
    all_pieces &= ~(1ULL << square); 

    char king_location = __builtin_ctzl(friendly_king); 
    //First see if the pinning piece is diagonally moving 
    uint64_t enemy_diagonal_sliders = Enemy.bishop | Enemy.queen; 
    uint64_t kingrays_diagonal = Moves::getBishopPseudoLegal(king_location, all_pieces);
    if((kingrays_diagonal & enemy_diagonal_sliders) != 0) {
        return kingrays_diagonal; 
    }

    //Otherwise it is a straight moving piece
    return Moves::getRookPseudoLegal(king_location, all_pieces); 
}