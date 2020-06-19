#include<vector>
#include<cstdint>
#include<iostream>
#include"bithacks.h"

void BitHacks::init() {

}

std::vector<char> BitHacks::serialize(uint64_t bitboard) {
    std::vector<char> squares; 

    while(bitboard) {
        //isolate lowest set bit
        uint64_t lsb = bitboard & -bitboard;

        //map to square 
        squares.push_back(__builtin_ctzl(lsb));

        bitboard &= bitboard-1;
    }
    return squares;
}