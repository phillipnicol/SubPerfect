#include<vector>
#include"board.h"
#include"moves.h"
#include"position.h"

std::vector<Move> Position::getMoves() {
    //get enemy attack arcs to decide if king is in check 


    //TODO


    //Loop through moves and make sure all are legal
    std::vector<Move> moves;
    for(std::vector<Move>::iterator it = moves.begin(); it != moves.end(); ++it) {
        //Check for legality 
    }
    return(moves);
}


void Position::setFEN(std::string FEN) {
    //TODO
}

//Print position to the terminal
//For debugging purposes 
void Position::printPosition() {
    char board[8][8];
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(White.PAWN & (1ULL << (8*i+j))) {board[i][j] = 'P';}
            if(White.ROOK & (1ULL << (8*i+j))) {board[i][j] = 'R';}
            if(White.BISHOP & (1ULL << (8*i+j))) {board[i][j] = 'B';}
            if(White.QUEEN & (1ULL << (8*i+j))) {board[i][j] = 'Q';}
            if(White.KING & (1ULL << (8*i+j))) {board[i][j] = 'K';}
            if(Black.PAWN & (1ULL << (8*i+j))) {board[i][j] = 'p';}
            if(Black.ROOK & (1ULL << (8*i+j))) {board[i][j] = 'r';}
            if(Black.BISHOP & (1ULL << (8*i+j))) {board[i][j] = 'b';}
            if(Black.QUEEN & (1ULL << (8*i+j))) {board[i][j] = 'q';}
            if(Black.QUEEN & (1ULL << (8*i+j))) {board[i][j] = 'k';}
        }
    }
}