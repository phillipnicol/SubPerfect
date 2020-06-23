#include<iostream>
#include<vector>
#include<cstdint> 
#include"piecemoves.h"

uint64_t PieceMoves::getRookPseudoLegal(char square, uint64_t blockers) {
    blockers &= RookMasks[square]; 

    uint64_t key = (blockers * ROOK_MAGICS[square]) >> (64 - ROOK_ATTACK_BITS[square]);
    return RookMagicBB[square][key]; 
}

uint64_t PieceMoves::getBishopPseudoLegal(char square, uint64_t blockers) {
    blockers &= BishopMasks[square];

    uint64_t key = (blockers * BISHOP_MAGICS[square]) >> (64 - BISHOP_ATTACK_BITS[square]);
    return BishopMagicBB[square][key]; 
}

uint64_t PieceMoves::getQueenPseudoLegal(char square, uint64_t blockers) {
    return (PieceMoves::getBishopPseudoLegal(square, blockers) | PieceMoves::getRookPseudoLegal(square, blockers));
}

uint64_t PieceMoves::getKingPseudoLegal(char square) {
    return KingMasks[square]; 
}

uint64_t PieceMoves::findPinnedPieces(Board Friendly, Board Enemy, uint64_t all_pieces) {
    uint64_t pinned = 0ULL;
    //If no king, simply return nothing
    if(Friendly.king == 0ULL) {return pinned;}

    //First we get moves from the opponent's sliding pieces 
    std::vector<char> rooks = serialize(Enemy.rook);
    std::vector<char> bishops = serialize(Enemy.bishop);
    std::vector<char> queens = serialize(Enemy.queen); 
    //diagonal
    uint64_t enemy_diagonals = 0ULL;
    for(int i = 0; i < bishops.size(); ++i) {
        enemy_diagonals |= PieceMoves::getBishopPseudoLegal(bishops[i], all_pieces);
    }
    for(int i = 0; i < queens.size(); ++i) {
        enemy_diagonals |= PieceMoves::getBishopPseudoLegal(queens[i], all_pieces);
    }
    enemy_diagonals &= ~Enemy.all;

    //straights
    uint64_t enemy_straights = 0ULL;
    for(int i = 0; i < rooks.size(); ++i) {
        enemy_straights |= PieceMoves::getRookPseudoLegal(rooks[i], all_pieces);
    }
    for(int i = 0; i < queens.size(); ++i) {
        enemy_straights |= PieceMoves::getRookPseudoLegal(rooks[i], all_pieces); 
    }
    enemy_straights &= ~Enemy.all; 

    //Now get sliding attacks from the king
    char king_location = __builtin_ctzl(Friendly.king);
    uint64_t kingrays_diagonal = PieceMoves::getBishopPseudoLegal(king_location, all_pieces);
    uint64_t kingrays_straight = PieceMoves::getRookPseudoLegal(king_location, all_pieces);  

    //Now we combine this information 
    pinned = (kingrays_diagonal & enemy_diagonals) | (kingrays_straight & enemy_straights);
    return pinned;
}

uint64_t PieceMoves::getPinnedMoves(char square, uint64_t friendly_king, Board Enemy, uint64_t all_pieces) {
    //Remove pinned piece from the board 
    all_pieces &= ~(1ULL << square); 

    char king_location = __builtin_ctzl(friendly_king); 
    //First see if the pinning piece is diagonally moving 
    uint64_t kingrays_diagonal = PieceMoves::getBishopPseudoLegal(king_location, all_pieces);
    if((kingrays_diagonal & (1ULL << square)) != 0) {
        //the pin is diagonal 
        uint64_t pinned_diagonal = PieceMoves::getBishopPseudoLegal(square, all_pieces);
        return (kingrays_diagonal & pinned_diagonal); 
    }
    //Otherwise it is a straight moving piece
    return (PieceMoves::getRookPseudoLegal(king_location, all_pieces) & PieceMoves::getRookPseudoLegal(square, all_pieces));
}