#include "MapHandler.h"
#include "Global.h"
#include "Game.h"
#include <string>
#include <iostream>

const unsigned int TEXTURE_CELL_SIZE = 16;

MapHandler::MapHandler(Game *game, std::string filename) : FILENAME(filename),
                                                           game(game)
{
    this->createMap();
    this->texture = this->game->getTexture("assets/Map16.png");
}

void MapHandler::createMap() {
    FILE *file = (FILE*)scp(fopen(this->FILENAME.c_str(), "r"));

    char character;
    std::vector<int> row;

    while (!feof(file)){
        character = getc(file);
        if (character != '\n'){
            row.push_back(atoi(&character));
        }else{
            this->map.push_back(row);
            row.clear();
        }
    }
    this->map.push_back(row);
    fclose(file);
}

void MapHandler::drawMap(SDL_Renderer* renderer){
    for(unsigned int i=0; i<this->map.size(); i++){
        for(unsigned int j=0; j<this->map[i].size(); j++){
            switch(this->map[i][j]){
                case 1: {
                    this->drawWall(renderer, j, i, (SDL_Color){HEX_COLOR(MAP_COLOR)});
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
}

void MapHandler::drawWall(SDL_Renderer *renderer, int x, int y, SDL_Color color){
    SDL_Rect srcRect = this->getSourceRect(x, y);
    SDL_Rect destRect = {static_cast<int>(CELL_SIZE * x), 
                         static_cast<int>(CELL_SIZE * y), 
                         static_cast<int>(CELL_SIZE / 1), 
                         static_cast<int>(CELL_SIZE / 1)};
    scc(SDL_RenderCopy(renderer, this->texture, &srcRect, &destRect));
}

SDL_Rect MapHandler::getSourceRect(int x, int y){
    if (y > 0 && y < this->map.size() && this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1)
        return (SDL_Rect){TEXTURE_CELL_SIZE * 10, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};

    // else if (x > 0 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1)
    //     return (SDL_Rect){TEXTURE_CELL_SIZE * 7, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};

    // else if (this->map[y + 1][x] == 1 && this->map[y][x + 1] == 1)
    //     return (SDL_Rect){TEXTURE_CELL_SIZE * 6, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};

    // else if (x > 0 && this->map[y][x - 1] == 1 && this->map[y + 1][x] == 1)
    //     return (SDL_Rect){TEXTURE_CELL_SIZE * 4, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};

    // else if (y > 0 && this->map[y - 1][x] == 1 && this->map[y][x + 1] == 1)
    //     return (SDL_Rect){TEXTURE_CELL_SIZE * 13, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};

    // else if (y > 0 && x > 0 && this->map[y - 1][x] == 1 && this->map[y][x - 1] == 1)
    //     return (SDL_Rect){TEXTURE_CELL_SIZE * 11, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};

    return (SDL_Rect){0, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE};
}