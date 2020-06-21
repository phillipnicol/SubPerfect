#include"catch.hpp"
#include"bithacks.h"
#include<iostream>

extern std::vector<uint64_t> RookMasks;
extern std::vector<uint64_t> BishopMasks;

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
    SECTION("BishopMask is constructed correctly") {
        //Test corners
        //A1
        REQUIRE(BishopMasks[0] == 18049651735527936ULL);
        //H1
        REQUIRE(BishopMasks[7] == 567382630219776ULL);
        //A8
        REQUIRE(BishopMasks[56] == 567382630219776ULL);
        //H8
        REQUIRE(BishopMasks[63] == 18049651735527936ULL);

        //Test middle of edges 
        REQUIRE(BishopMasks[24] == 2256206450263040ULL);
        REQUIRE(BishopMasks[60] == 11333774449049600ULL);
        REQUIRE(BishopMasks[39] == 9077569074761728ULL);
        REQUIRE(BishopMasks[3] == 1075975168ULL); 

        //Test middle of board
        REQUIRE(BishopMasks[35] == 9592139778506752ULL);
        REQUIRE(BishopMasks[21] == 567383701868544ULL);
    }
}
