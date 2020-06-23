#include<iostream>
#include<string>
#include<cstdint> 

#include"perft.h"

uint64_t Perft::Perft(Position pos, int depth) {
    uint64_t nmoves = 0;
    uint64_t nodes = 0;

    std::vector<Move> moves = pos.getMoves(); 
    nmoves = moves.size(); 

    if(depth == 1) {
        return nmoves;
    }

    for(auto move : moves) {
        Position oldpos = Moves::makeMove(pos, move);
        nodes += Perft::Perft(pos, depth - 1);
        pos = oldpos;
    }
    return nodes; 
}