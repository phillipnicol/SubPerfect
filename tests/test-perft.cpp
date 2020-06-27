#include"catch.hpp"
#include"perft.h" 

TEST_CASE("General Perft results are correct") {
    

    SECTION("Piece moves are being generated correctly") {
        REQUIRE(Perft::Perft("rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w - - 0 1", 4, false) == 4200525);
    }
}