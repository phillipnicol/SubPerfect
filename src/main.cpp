#include"bithacks.h"
#include"position.h" 

int main() {
    BitHacks::init();

    Position position; 
    position.setFEN(STARTING_POSITION);
    position.printPosition();
}