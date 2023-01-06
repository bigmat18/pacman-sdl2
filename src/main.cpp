#include "Game.h"

int main(void){
    Game game;
    bool success = game.initialize();
    if (success) game.runLoop();

    game.shutdown();
    return 0;
}