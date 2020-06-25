#define CATCH_CONFIG_RUNNER
#include"catch.hpp"
#include"perft.h" 

int main() {
    PieceTables::init();

    int result = Catch::Session().run();

    return result;
}