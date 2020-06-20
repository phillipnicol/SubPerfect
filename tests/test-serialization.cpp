#include"catch.hpp"
#include"bithacks.h"

TEST_CASE("Serialization is correct") {
    uint64_t BB;
    std::vector<char> squares; 
    SECTION("Empty bitboard returns nothing.") {
        BB = 0;
        squares = BitHacks::serialize(BB);
        REQUIRE(squares.size() == 0);        
    }
    SECTION("Single squares are handled correctly") {
        for(int i = 0; i < 64; ++i) {
            BB = 1ULL << i;
            squares = BitHacks::serialize(BB);
            REQUIRE(squares.size() == 1); REQUIRE(squares[0] == i);
        }        
    }
    SECTION("A few elements are handled correctly") {
        BB = (1ULL << 33) + (1ULL << 50) + (1ULL << 2);
        squares = BitHacks::serialize(BB);
        REQUIRE(squares.size() == 3); REQUIRE(squares[1] == 33);        
    }
    SECTION("All elements") {
        BB = 0;
        for(int i = 0; i < 64; ++i) {
            BB += (1ULL << i);
        }
        squares = BitHacks::serialize(BB);
        REQUIRE(squares.size() == 64); REQUIRE(squares[5] == 5);
    }
}
