#include<iostream>
#include<cstdint> 

#include"bithacks.h"
#include"position.h" 

int main() {
    BitHacks::init();

    Position starting_position; 
    starting_position.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    starting_position.printPosition();
}