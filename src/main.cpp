#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(void){
    FILE* file = fopen("map.txt", "r");
    if (file == nullptr) {
        std::cout << "Errore" << std::endl;
        return EXIT_FAILURE;
    }

    unsigned char character = 0;

    while (!feof(file)){
        character = getc(file);
        std::cout << character << "-";
    }
    std::cout << std::endl;
    fclose(file);

    Game game;
    bool success = game.initialize();
    if (success) game.runLoop();

    game.shutdown();
    return 0;
}