#include<iostream>
#include<string>
#include<cstdint> 
#include<chrono> 

#include"perft.h"

uint64_t Perft::Perft(std::string FEN, int depth, bool verbose) {
    Position pos;
    pos.setFEN(FEN); 

    auto start = std::chrono::high_resolution_clock::now(); 
    uint64_t nodes = Perft::PerftMain(pos, depth); 
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = stop - start;

    double nps = 1000*(nodes/duration.count());

    if(verbose) {
        std::cout << "+----+----+----+----+----+----+----+----+" << std::endl << std::endl;
        std::cout << "             Perft results" << std::endl << std::endl;
        std::cout << "Starting position: " << FEN << std::endl << std::endl;
        std::cout << "Nodes searched: " << std::fixed << nodes  << std::endl << std::endl; 
        std::cout << "Nodes per second: " << nps << std::endl << std::endl; 
        std::cout << "+----+----+----+----+----+----+----+----+" << std::endl;
    }
    return nodes; 
}

uint64_t Perft::PerftMain(Position pos, int depth) {
    uint64_t nodes = 0;
    std::vector<Move> moves = Moves::generateMoves(pos);  

    if(depth == 1) {
        for(auto move : moves) {
            if(pos.isLegal(move)) {
                ++nodes;
            }
        }
        return nodes; 
    }
    for(auto move : moves) {
        if(pos.isLegal(move)) {
            Moves::makeMove(pos, move);
            nodes += Perft::PerftMain(pos, depth - 1);
            Moves::unmakeMove(pos, move);         
        }
    }
    return nodes; 
}

