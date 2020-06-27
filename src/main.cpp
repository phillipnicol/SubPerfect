#include"perft.h"

int main() {
    PieceTables::init();

    Perft::Perft("rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w - - 0 1", 4, true);
}