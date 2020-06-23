#include<iostream>

#include"position.h"

int main() {
    PieceTables::init();

    Position position;
    position.setFEN(STARTING_POSITION);
    position.printPosition();
}