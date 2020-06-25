#include"catch.hpp"
#include"perft.h" 

TEST_CASE("King move generation is correct") {
    SECTION("Kings on an open board") {
        REQUIRE(Perft::Perft("8/8/8/3K4/8/4k3/8/8 w - - 0 1", 4, false) == 2284); 
    }
}