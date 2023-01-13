#include "MapHandler.h"
#include "Global.h"
#include "Game.h"
#include <string>
#include <iostream>

const unsigned int TEXTURE_CELL_SIZE = 16;

MapHandler::MapHandler(Game *game, std::string filename) : FILENAME(filename),
                                                           game(game)
{
    this->createMapMatrix();
    this->texture = this->game->getTexture("assets/Map16.png");
    this->createRectsMatrix();
}

MapHandler::~MapHandler() {
    for(int i=0; i<this->rects.size(); i++){
        for(int j=0; j<this->rects[i].size(); j++){
            if (this->rects[i][j]) delete this->rects[i][j];
        }
    }
}

void MapHandler::createMapMatrix(){
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
    row.pop_back();
    this->map.push_back(row);
    fclose(file);
}

void MapHandler::createRectsMatrix(){
    std::vector<SDL_Rect*> row;

    for(int i=0; i<this->map.size(); i++){
        for(int j=0; j<this->map[i].size(); j++){
            if(this->map[i][j]) row.push_back(this->getSourceRect(j, i));
            else row.push_back(NULL);
        }
        this->rects.push_back(row);
        row.clear();
    }
}

void MapHandler::drawMap(SDL_Renderer* renderer){
    for(int i=0; i<this->map.size(); i++){
        for(int j=0; j<this->map[i].size(); j++){
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
    SDL_Rect destRect = {static_cast<int>(CELL_SIZE * x), 
                         static_cast<int>(CELL_SIZE * y), 
                         static_cast<int>(CELL_SIZE), 
                         static_cast<int>(CELL_SIZE)};
    scc(SDL_RenderCopy(renderer, this->texture, this->rects[y][x], &destRect));
}

SDL_Rect* MapHandler::getSourceRect(int x, int y){
    int pos = 0;

    if (y > 0 && y < this->map.size() - 1 && x > 0 && x < this->map[y].size() - 1 && 
        this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 15;

    else if (y > 0 && x > 0 && x < this->map[y].size() - 1 && 
            this->map[y - 1][x] == 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 14;

    else if (y < this->map.size() - 1 && x > 0 && x < this->map[y].size() - 1 && 
            this->map[y + 1][x] == 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 7;

    else if (y > 0 && x > 0 && y < this->map.size() - 1 &&
             this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1 && this->map[y][x - 1] == 1) pos = TEXTURE_CELL_SIZE * 11;

    else if (y > 0 && y < this->map.size() - 1 && x < this->map[y].size() - 1 &&
             this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 13;

    else if (y > 0 && y < this->map.size() - 1 && this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1) pos = TEXTURE_CELL_SIZE * 9;

    else if (x > 0 && x < this->map[y].size() - 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 6;

    else if (y < this->map[y].size() - 1 && x < this->map[y].size() - 1 && this->map[y + 1][x] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 5;

    else if (x > 0 && y < this->map.size() - 1 && this->map[y][x - 1] == 1 && this->map[y + 1][x] == 1) pos = TEXTURE_CELL_SIZE * 3;

    else if (y > 0 && x < this->map[y].size() - 1 && this->map[y - 1][x] == 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 12;

    else if (y > 0 && x > 0 && this->map[y - 1][x] == 1 && this->map[y][x - 1] == 1) pos = TEXTURE_CELL_SIZE * 10;

    else if (y > 0 && this->map[y - 1][x] == 1) pos = TEXTURE_CELL_SIZE * 8;

    else if (y < this->map.size() - 1 && this->map[y + 1][x] == 1) pos = TEXTURE_CELL_SIZE * 1;

    else if (x > 0 && this->map[y][x - 1] == 1) pos = TEXTURE_CELL_SIZE * 2;

    else if (x < this->map[y].size() - 1 && this->map[y][x + 1] == 1) pos = TEXTURE_CELL_SIZE * 4;

    return new SDL_Rect({pos, 0, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE});
}