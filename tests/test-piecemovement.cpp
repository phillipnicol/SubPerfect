#include"catch.hpp"
#include"perft.h" 

TEST_CASE("Piece generation is is correct") {
    SECTION("Kings") {
        REQUIRE(Perft::Perft("8/8/8/3K4/8/4k3/8/8 w - - 0 1", 4, false) == 2284); 
    }
    SECTION("Queens") {
        REQUIRE(Perft::Perft("KQ6/QQ6/8/8/8/8/6qq/6qk b - - 0 1", 4, false) == 798835);
    }
    SECTION("Bishops") {
        REQUIRE(Perft::Perft("K7/BB6/bb6/8/8/8/8/k6b w - - 0 1", 4, false) == 41060);
    }
    SECTION("Knights") {
        REQUIRE(Perft::Perft("K7/8/3N4/4n3/8/8/8/7k w - - 0 1", 6, false) == 1355713);
    }
    SECTION("Rooks") {
        REQUIRE(Perft::Perft("KR5r/8/4R3/3r4/8/8/8/kr5R w - - 0 1", 4, false) == 968642);
    }
}
