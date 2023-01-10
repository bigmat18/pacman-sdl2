#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(void){

    Game game;
    bool success = game.initialize();
    if (success) game.runLoop();

    game.shutdown();
    return 0;
}