#include<vector>

#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED

//Move struct
//origin and destination between 0 and 63
struct Move {
    char origin, destination;
};

extern std::vector<std::vector<uint64_t> > Rays;

#endif