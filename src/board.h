#include<cstdint>

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

struct Board {
    uint64_t ALL;
    uint64_t PAWN;
    uint64_t ROOK;
    uint64_t KNIGHT;
    uint64_t BISHOP;
    uint64_t QUEEN;
    uint64_t KING;
};

#endif