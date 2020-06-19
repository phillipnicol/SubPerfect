#include"board.h"
#include"moves.h"

#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

class Position {
    public:
        //Information about the pieces
        Board White, Black;

        //general game information
        bool white_to_move; 
        bool white_castle, black_castle; //castling
        bool prev_move_pawn; //was the last move a pawn? For en passant
        Move* prev_move; //pointer to the previous move 

        //Methods
        //Find the list of legal moves 
        std::vector<Move> getMoves();

        //print board to terminal
        void printPosition();
};

#endif 