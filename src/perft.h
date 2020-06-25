#include"moves.h"

#ifndef PERFT_H_INCLUDED
#define PERFT_H_INCLUDED

namespace Perft { 
    uint64_t Perft(std::string FEN, int depth, bool verbose);
    uint64_t PerftMain(Position pos, int depth);
}

#endif 