#include<vector>
#include<cstdint> 

#ifndef BITHACKS_H_INCLUDED
#define BITHACKS_H_INCLUDED

#define FILE_A 0x101010101010101ULL
#define FILE_B 0x202020202020202ULL
#define FILE_C 0x404040404040404ULL
#define FILE_D 0x808080808080808ULL
#define FILE_E 0x1010101010101010ULL
#define FILE_F 0x2020202020202020ULL
#define FILE_H 0x8080808080808080ULL

#define RANK_1 0xffULL
#define RANK_2 0xff00ULL
#define RANK_3 0xff0000ULL
#define RANK_4 0xff000000ULL
#define RANK_5 0xff00000000ULL
#define RANK_6 0xff0000000000ULL
#define RANK_7 0xff000000000000ULL
#define RANK_8 0xff00000000000000ULL

std::vector<std::vector<uint64_t> > makeRays(); 

namespace BitHacks {
    void init();
    std::vector<char> serialize(uint64_t bitboard);
    void makeMasks(std::vector<std::vector<uint64_t> > &Rays);
    void printBitBoard(uint64_t BB);
}

enum Directions {N, NE, E, SE, S, SW, W, NW};

#endif 