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




//Print position to the terminal
//For debugging purposes 
void Position::printPosition() {
    //TODO 
}