#include"catch.hpp"
#include"bithacks.h"
#include<iostream>

extern std::vector<uint64_t> RookMasks;

TEST_CASE("Masks for sliding pieces is correct") {
    BitHacks::init();
    SECTION("RookMask is constructed correctly") {
        //Test corners
        //A1
        REQUIRE(RookMasks[0] == 282578800148862ULL);
        //H1
        REQUIRE(RookMasks[7] == 36170086419038334ULL);
        //A8
        REQUIRE(RookMasks[56] == 9079539427579068672ULL);
        //H8
        REQUIRE(RookMasks[63] == 9115426935197958144ULL);

        //Test middle of edges
        REQUIRE(RookMasks[24] == 282580897300736ULL);
        REQUIRE(RookMasks[60] == 7930856604974452736ULL);
        REQUIRE(RookMasks[39] == 36170077829103616ULL);
        REQUIRE(RookMasks[3] == 2260630401190006ULL); 

        //Test in the middle of the board 
        REQUIRE(RookMasks[35] == 2261102847592448ULL);
        REQUIRE(RookMasks[21] == 9042521608822784ULL);
    }
}
