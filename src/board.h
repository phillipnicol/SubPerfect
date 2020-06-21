#include<cstdint>

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

struct Board {
    uint64_t all;
    uint64_t pawn;
    uint64_t rook;
    uint64_t knight;
    uint64_t bishop;
    uint64_t queen;
    uint64_t king;
};

#endif