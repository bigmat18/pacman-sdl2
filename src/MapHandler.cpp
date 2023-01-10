#include "MapHandler.h"
#include "Global.h"
#include <string>
#include <iostream>

MapHandler::MapHandler(std::string filename) : FILENAME(filename) 
{this->createMap();}

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
    scc(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
    SDL_Rect rect = {static_cast<int>(CELL_SIZE * x), 
                     static_cast<int>(CELL_SIZE * y), 
                     CELL_SIZE, 
                     CELL_SIZE};
    scc(SDL_RenderFillRect(renderer, &rect));
}