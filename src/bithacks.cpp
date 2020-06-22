#include<vector>
#include<cstdint>
#include<iostream>
#include<algorithm> 
#include"bithacks.h"

std::vector<uint64_t> BishopMasks(64,0);
std::vector<uint64_t> RookMasks(64,0);

std::vector<std::vector<uint64_t> > BishopMagicBB(64, std::vector<uint64_t>()); 
std::vector<std::vector<uint64_t> > RookMagicBB(64, std::vector<uint64_t>()); 

void BitHacks::init() {
    std::vector<std::vector<uint64_t> > Rays = makeRays();
    BitHacks::makeMasks(Rays);

    BitHacks::fillBishopMagicBB(Rays);   
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

void BitHacks::fillBishopMagicBB(std::vector<std::vector<uint64_t> > &Rays) {
    //Ensure that the vector is initialized with all 0's    
    for(int i = 0; i < 64; ++i) {
        BishopMagicBB[i].clear();
        BishopMagicBB[i] = std::vector<uint64_t> ((1 << BishopAttackBits[i]), 0); 

        for(int j = 0; j < (1 << BishopAttackBits[i]); ++j) {
            uint64_t blocker = getBlocker(j, BishopMasks[i]); 
            uint64_t bishop_attack = getBishopAttacksFromBlocker(i, blocker, Rays);

            uint64_t index_mapping = blocker * BishopMagics[i];
            //Get key by shifting back
            uint64_t key = index_mapping >> (64 - BishopAttackBits[i]); 
            BishopMagicBB[i][key] = bishop_attack; 
        }
    }
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
            uint64_t key = index_mapping >> (64 - RookAttackBits[i]); 
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

uint64_t getBishopAttacksFromBlocker(int square, uint64_t blocker, std::vector<std::vector<uint64_t> > &Rays) {
    //Do each direction 
    //NE
    uint64_t ne_attack = Rays[NE][square]; 
    std::vector<char> on_bits = BitHacks::serialize(blocker & Rays[NE][square]); 
    std::vector<char>::iterator c; 
    if(on_bits.size() > 0) {
        c = std::min_element(on_bits.begin(), on_bits.end());
        ne_attack &= (Rays[SW][*c] | (1ULL << *c));         
    }

    //SE  
    uint64_t se_attack = Rays[SE][square]; 
    on_bits = BitHacks::serialize(blocker & Rays[SE][square]); 
    if(on_bits.size() > 0) {
        c = std::max_element(on_bits.begin(), on_bits.end());
        se_attack &= (Rays[NW][*c] | (1ULL << *c)); 
    }

    //SW 
    uint64_t sw_attack = Rays[SW][square]; 
    on_bits = BitHacks::serialize(blocker & Rays[SW][square]); 
    if(on_bits.size() > 0) {
        c = std::max_element(on_bits.begin(), on_bits.end());
        sw_attack &= (Rays[NE][*c] | (1ULL << *c));        
    }

    //NW
    uint64_t nw_attack = Rays[NW][square]; 
    on_bits = BitHacks::serialize(blocker & Rays[NW][square]); 
    if(on_bits.size() > 0) {
        c = std::min_element(on_bits.begin(), on_bits.end());
        nw_attack &= (Rays[SE][*c] | (1ULL << *c));         
    }

    return (nw_attack | se_attack | sw_attack | ne_attack);     
}

uint64_t getRookAttacksFromBlocker(int square, uint64_t blocker, std::vector<std::vector<uint64_t> > &Rays) {
    //Do each direction 
    //North 
    uint64_t north_attack = Rays[N][square]; 
    std::vector<char> on_bits = BitHacks::serialize(blocker & Rays[N][square]); 
    std::vector<char>::iterator c; 
    if(on_bits.size() > 0) {
        c = std::min_element(on_bits.begin(), on_bits.end());
        north_attack &= (Rays[S][*c] | (1ULL << *c));         
    }

    //East 
    uint64_t east_attack = Rays[E][square]; 
    on_bits = BitHacks::serialize(blocker & Rays[E][square]); 
    if(on_bits.size() > 0) {
        c = std::min_element(on_bits.begin(), on_bits.end());
        east_attack &= (Rays[W][*c] | (1ULL << *c)); 
    }

    //South 
    uint64_t south_attack = Rays[S][square]; 
    on_bits = BitHacks::serialize(blocker & Rays[S][square]); 
    if(on_bits.size() > 0) {
        c = std::max_element(on_bits.begin(), on_bits.end());
        south_attack &= (Rays[N][*c] | (1ULL << *c));        
    }

    //West
    uint64_t west_attack = Rays[W][square]; 
    on_bits = BitHacks::serialize(blocker & Rays[W][square]); 
    if(on_bits.size() > 0) {
        c = std::max_element(on_bits.begin(), on_bits.end());
        west_attack &= (Rays[E][*c] | (1ULL << *c));         
    }

    return (north_attack | east_attack | south_attack | west_attack); 
}
