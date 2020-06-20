#include<vector>
#include<cstdint> 

#ifndef BITHACKS_H_INCLUDED
#define BITHACKS_H_INCLUDED

void makeRays(); 

namespace BitHacks {
    void init();
    std::vector<char> serialize(uint64_t bitboard);
    void printBitBoard(uint64_t BB);
}

enum Directions {N, NE, E, SE, S, SW, W, NW};

#endif 