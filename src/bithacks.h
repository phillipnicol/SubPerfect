#include<cstdint>

#ifndef BITHACKS_H_INCLUDED
#define BITHACKS_H_INCLUDED

//serialize returns a vector of char consisting of the activated squares in a given bitboard
//Taken from chess programming wiki 
inline std::vector<char> serialize(uint64_t bitboard) {
    std::vector<char> squares; 

    while(bitboard) {
        //isolate lowest set bit
        uint64_t lsb = bitboard & -bitboard;

        //map to square 
        //__builtin_ctzl for g++ counts the number of leading zeros on the power of two found above
        squares.push_back(__builtin_ctzl(lsb));

        bitboard &= bitboard-1;
    }
    return squares;
}

inline void printBitBoard(uint64_t BB) {
    //print the bitboard in a way that looks correct
    for(int i = 56; i >= 0; i -= 8) {
        for(int j = i; j < i + 8; ++j) {
            if(BB & (1ULL << j)) {
                std::cout << 1 << " ";
            }
            else {
                std::cout << 0 << " ";
            }
        }
        std::cout << "\n";
    }
}


#endif