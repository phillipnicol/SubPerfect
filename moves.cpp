#include<cstdint>
#include<iostream>
#include<vector>
#include"position.h"
#include"moves.h"
#include"bithacks.h"

namespace Moves {
    std::vector<Move> getRookMoves(Position position) {
        uint64_t all_pieces = position.White.ALL | position.Black.ALL; 
        uint64_t player_pieces = position.white_to_move ? position.White.ALL : position.Black.ALL;
        uint64_t rooks = position.white_to_move ? position.White.ROOK : position.Black.ROOK;

        //get squares
        std::vector<char> squares = BitHacks::serialize(rooks);
        
        //loop over squares 
    }
}