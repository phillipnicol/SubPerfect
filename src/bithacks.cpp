#include<vector>
#include<cstdint>
#include<iostream>
#include"bithacks.h"

std::vector<uint64_t> BishopMasks(64,0);
std::vector<uint64_t> RookMasks(64,0);

std::vector<std::vector<uint64_t> > RookMagicBB(64, std::vector<uint64_t>()); 

void BitHacks::init() {
    std::vector<std::vector<uint64_t> > Rays = makeRays();
    BitHacks::makeMasks(Rays);
    
    BitHacks::fillRookMagicBB(Rays);
}

//serialize returns a vector of char consisting of the activated squares in a given bitboard
//Taken from chess programming wiki 
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

void BitHacks::fillRookMagicBB(std::vector<std::vector<uint64_t> > &Rays) {
    //Ensure that the vector is initialized with all 0's 
    for(int i = 0; i < 64; ++i) {
        RookMagicBB[i].clear(); 
        RookMagicBB[i] = std::vector<uint64_t> ((1 << RookAttackBits[i]), 0);
        for(int j = 0; j < (1 << RookAttackBits[i]); ++j) {
            uint64_t blocker = getBlocker(j, RookMasks[i]); 
            uint64_t rook_attack = getRookAttacksFromBlocker(i, blocker, Rays); 
            
            uint64_t index_mapping = blocker * RookMagics[i];
            //Get key by shifting back
            int key = index_mapping >> (64 - RookAttackBits[i]); 
            RookMagicBB[i][key] = rook_attack; 
        }
    }
}

void BitHacks::makeMasks(std::vector<std::vector<uint64_t> > &Rays) {
    uint64_t edgesquares = FILE_A | FILE_H | RANK_1 | RANK_8;     
    for(int i = 0; i < 64; ++i) {
        BishopMasks[i] = (Rays[NE][i] | Rays[SE][i] | Rays[SW][i] | Rays[NW][i]) & ~edgesquares; 
        RookMasks[i] = (Rays[N][i] & ~RANK_8) | (Rays[E][i] & ~FILE_H) | (Rays[S][i] & ~RANK_1) | (Rays[W][i] & ~FILE_A); 
    }
}

void BitHacks::printBitBoard(uint64_t BB) {
    //print it in a way that looks correct
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

std::vector<std::vector<uint64_t> > makeRays() {
    std::vector<std::vector<uint64_t> > Rays(8, std::vector<uint64_t>(64,0)); 
    int counter;
    uint64_t newray; 
    for(int i = 0; i < 64; ++i) {
        //Do each direction
        //North
        counter = i+8;
        newray = 0;
        while(counter < 64) {
            newray += 1ULL << counter;
            counter += 8;
        }
        Rays[N][i] = newray; 

        //Northeast
        counter = i+9;
        newray = 0;
        while(counter < 64 && (counter-9) % 8 != 7) {
            newray += 1ULL << counter;
            counter += 9;
        }
        Rays[NE][i] = newray; 

        //East
        counter = i+1;
        newray = 0;
        while(counter % 8 != 0) {
            newray += 1ULL << counter;
            counter++;
        }
        Rays[E][i] = newray; 

        //Southeast
        counter = i-7;
        newray = 0;
        while(counter >= 0 && (counter+7) % 8 != 7) {
            newray += 1ULL << counter;
            counter -= 7;
        }
        Rays[SE][i] = newray; 

        //South
        counter = i-8;
        newray = 0;
        while(counter >= 0) {
            newray += 1ULL << counter;
            counter -= 8;
        }
        Rays[S][i] = newray;

        //Southwest
        counter = i-9;
        newray = 0;
        while(counter >= 0 && (counter+9) % 8 != 0) {
            newray += 1ULL << counter;
            counter -= 9;
        }
        Rays[SW][i] = newray; 

        //West
        counter = i-1;
        newray = 0;
        while((counter + 1) % 8 != 0) {
            newray += 1ULL << counter;
            counter--;
        }
        Rays[W][i] = newray;

        //Northwest
        counter = i+7;
        newray = 0;
        while(counter < 64 && (counter-7) % 8 != 0) {
            newray += 1ULL << counter;
            counter += 7; 
        }
        Rays[NW][i] = newray;
    }
    return Rays; 
}

uint64_t getBlocker(int index, uint64_t mask) {
    uint64_t blocker = 0ULL;
    std::vector<char> on_bits = BitHacks::serialize(mask);
    for(int i = 0; i < on_bits.size(); ++i) {
        if(index & (1 << i)) {
            blocker += 1ULL << on_bits[i];
        }
    }
    return blocker;
}

uint64_t getRookAttacksFromBlocker(int square, uint64_t blocker, std::vector<std::vector<uint64_t> > &Rays) {
    uint64_t rook_attack = Rays[N][square] | Rays[E][square] | Rays[S][square] | Rays[W][square]; 

    std::vector<char> on_bits = BitHacks::serialize(blocker); 

    for(int i = 0; i < on_bits.size(); ++i) {
        if(i < square) {
            rook_attack &= (Rays[N][i] | Rays[E][i]);
        }
        else {
            rook_attack &= (Rays[S][i] | Rays[W][i]); 
        }
    }
    return rook_attack; 
}