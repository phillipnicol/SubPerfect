#include"perft.h"

int main() {
    PieceTables::init();

    Position pos;
    pos.setFEN("8/8/8/8/8/8/P7/3k3K w - - 0 1");
    pos.printPosition(); 

    Perft::Perft("8/8/8/8/8/8/P7/3k3K w - - 0 1", 6, true);
}