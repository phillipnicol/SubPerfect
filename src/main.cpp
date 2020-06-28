#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("7k/1p6/P7/8/8/8/8/7K w - - 0 1");
    pos.printPosition(); 

    Perft::Perft("7k/1p6/P7/8/8/8/8/7K w - - 0 1", 6, true);
}