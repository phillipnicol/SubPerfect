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

extern std::vector<std::vector<uint64_t> > BishopMagicBB;
extern std::vector<std::vector<uint64_t> > RookMagicBB;


#endif