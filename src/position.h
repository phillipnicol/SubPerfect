#include<string>
#include"piecemoves.h"

#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

enum Color {WHITE, BLACK}; 

class Position {
    public:
        //Piece bitboards 
        Board Pieces[2]; // 0 is white bitboards while 1 is black 

        //general game information
        bool color; // 0 is white while 1 is black 
        bool castling[4];
        char en_passant_target; //will be 65 if no en passant target 
        int halfmove_clock; //For 50 move draws
        int fullmove_number; 
        bool incheck; // is the side to move in check 

        //useful datamembers 
        uint64_t all; 
        uint64_t pinned; 
        uint64_t safety_map; 
        int kingsq; 

        //Public member functions
        bool isinCheck(); 
        bool isLegal(Move move); 

        //set up position
        void setFEN(std::string FEN); 

        //output the position 
        void printPosition();
};

inline bool Position::isinCheck() {
    int king_loc = _tzcnt_u64(Pieces[color].king);
    incheck = squareAttacked(king_loc, Pieces[color].all | Pieces[!color].all, Pieces[!color]);
    return incheck; 
}

inline bool Position::isLegal(Move move) {
    if(move.aggressor == KING) {
        Board mycopy = Pieces[color];
        uint64_t dest = 1ULL << move.destination;  
        uint64_t orig = ~(1ULL << move.origin);   

        mycopy.king &= orig;
        mycopy.king |= dest;   

        mycopy.all &= orig; mycopy.all |= dest;   

        //enemy
        dest = ~dest; 
        Board enemycopy = Pieces[!color];
        enemycopy.all &= dest;
        enemycopy.pawn &= dest; enemycopy.rook &= dest; enemycopy.knight &= dest; 
        enemycopy.bishop &= dest; enemycopy.queen &= dest;

        return !squareAttacked(move.destination, mycopy.all | enemycopy.all, enemycopy); 
    }
    else {
        return true; 
    }
    /*uint64_t dest = 1ULL << move.destination;  
    uint64_t orig = ~(1ULL << move.origin);

    Board mycopy = Pieces[color]; 
    switch(move.aggressor) {
        case PAWN: break;
        case ROOK:
            mycopy.rook &= orig;
            mycopy.rook |= dest; 
            break;
        case KNIGHT: break; 
        case BISHOP:
            mycopy.bishop &= orig;
            mycopy.bishop |= dest; 
            break;
        case QUEEN:
            mycopy.queen &= orig;
            mycopy.queen |= dest; 
            break;
        case KING:
            mycopy.king &= orig;
            mycopy.king |= dest; 
            break;         
    }
    mycopy.all &= orig; mycopy.all |= dest; 

    //enemy
    dest = ~dest; 
    Board enemycopy = Pieces[!color];
    enemycopy.all &= dest;
    enemycopy.pawn &= dest; enemycopy.rook &= dest; enemycopy.knight &= dest; 
    enemycopy.bishop &= dest; enemycopy.queen &= dest;

    int king_loc = _tzcnt_u64(mycopy.king); 
    return !squareAttacked(king_loc, mycopy.all | enemycopy.all, enemycopy); */
}

//starting position 
const std::string STARTING_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

#endif 