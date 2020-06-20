#include<vector>
#include<cstdint>
#include<iostream>
#include"bithacks.h"

std::vector<std::vector<uint64_t> > Rays(8, std::vector<uint64_t>(64,0));

void BitHacks::init() {
    makeRays();
}

std::vector<char> BitHacks::serialize(uint64_t bitboard) {
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

void makeRays() {
    int counter;
    uint64_t newray; 
    for(int i = 0; i < 64; ++i) {
        //Do each direction
        //North
        counter = i+8;
        newray = 0;
        while(counter < 64) {
            newray += 1 << counter;
            counter += 8;
        }
        Rays[N][i] = newray; 

        //Northeast
        //TODO

        //East
        counter = i+1;
        newray = 0;
        while(counter % 8 != 0) {
            newray += 1 << counter;
            counter++;
        }
        Rays[E][i] = newray; 

        //Southeast
        //TODO

        //South
        counter = i-8;
        newray = 0;
        while(counter > 0) {
            newray += 1 << counter;
            counter -= 8;
        }
        Rays[S][i] = newray;

        //Southwest
        //TODO

        //West
        counter = i-1;
        newray = 0;
        while((counter + 1) % 8 != 0) {
            newray += 1 << counter;
            counter--;
        }
        Rays[W][i] = newray;

        //Northwest
        //TODO
    }
}

void BitHacks::printBitBoard(uint64_t BB) {
    //print it in a way that looks correct
    for(int i = 56; i >= 0; i -= 8) {
        for(int j = i; j < i + 8; ++j) {
            if(BB & (1ULL << (i+j))) {
                std::cout << 1 << " ";
            }
            else {
                std::cout << 0 << " ";
            }
        }
        std::cout << "\n";
    }
}