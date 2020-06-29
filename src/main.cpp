#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("7k/Pp6/8/8/8/8/8/7K w - - 0 1");
    pos.printPosition(); 

    Perft::Perft("8/Pp6/8/2k5/8/8/8/7K w - - 0 1", 4, true);
}