#include<string>
#include"board.h"
#include"moves.h"

#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

enum Color {WHITE, BLACK}; 

class Position {
    public:
        //Piece bitboards 
        Board Pieces[2]; 

        //general game information
        bool color; 
        bool castling[4];
        char en_passant_target; //will be 65 if no en passant target 
        int halfmove_clock; //For 50 move draws
        int fullmove_number; 

        //Public member functions
        //Find the list of legal moves 
        std::vector<Move> getMoves();

        //set up position
        void setFEN(std::string FEN); 

        //print board to terminal
        void printPosition();
    
    private:
        uint64_t all_pieces; 

        //Private member functions  
        void getRookMoves(std::vector<Move> &Moves); 
        void getBishopMoves(std::vector<Move> &Moves); 
};

//starting position 
const std::string STARTING_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

#endif 