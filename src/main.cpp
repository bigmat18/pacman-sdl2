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

    char character;
    std::vector<std::vector<int>> MAP;
    std::vector<int> row;

    while (!feof(file)){
        character = getc(file);
        if(character != '\n'){
            row.push_back(atoi(&character));
        }else{
            MAP.push_back(row);
            row.clear();
        }
    }
    fclose(file);

    Game *game = new Game(&MAP);
    bool success = game->initialize();
    if (success) game->runLoop();

    game->shutdown();
    return 0;
}