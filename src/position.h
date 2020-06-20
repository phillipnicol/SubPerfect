#include<string>
#include"board.h"
#include"moves.h"

#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

class Position {
    public:
        //Piece bitboards 
        Board White, Black;

        //general game information
        bool white_to_move; 
        bool castling[4];
        char en_passant_target; //will be 65 if no en passant target 

        //Methods
        //Find the list of legal moves 
        std::vector<Move> getMoves();

        //set up position
        void setFEN(std::string FEN); 

        //print board to terminal
        void printPosition();
};

#endif 