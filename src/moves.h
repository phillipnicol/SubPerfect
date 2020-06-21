#include<vector>
#include<cstdint>

#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED

//Move struct
//origin and destination between 0 and 63
struct Move {
    char origin, destination;
};

namespace Moves {
    uint64_t getRookPseudoLegal(char square, uint64_t blockers); 
};

extern std::vector<uint64_t> BishopMasks;
extern std::vector<uint64_t> RookMasks;

extern std::vector<std::vector<uint64_t> > BishopMagicBB;
extern std::vector<std::vector<uint64_t> > RookMagicBB;

#endif