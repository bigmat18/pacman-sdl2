#include "MapHandler.h"
#include "Global.h"
#include "Game.h"
#include <string>
#include <iostream>

MapHandler::MapHandler(Game *game, std::string filename) : FILENAME(filename),
                                                           game(game)
{
    this->createMapMatrix();
    this->texture = this->game->getTexture("assets/Map16.png");
    this->createElementsMatrix();
}

MapHandler::~MapHandler() {
    for(int i=0; i<this->elements.size(); i++){
        delete this->elements[i]->rect;
        delete this->elements[i];
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

void MapHandler::createElementsMatrix(){

    for(int i=0; i<this->map.size(); i++){
        for(int j=0; j<this->map[i].size(); j++){
            if(this->map[i][j] != 0) this->elements.push_back(new Element({j, i, this->getSourceRect(j, i, (MapType)(this->map[i][j])), (MapType)(this->map[i][j])}));
        }
    }
}

void MapHandler::drawMap(SDL_Renderer* renderer){
    for(int i = 0; i < this->elements.size(); i++){
        this->drawElement(renderer, this->elements[i]->x, this->elements[i]->y, this->elements[i]->rect);
    }
}


void MapHandler::drawElement(SDL_Renderer *renderer, int x, int y, SDL_Rect* srcRect){
    SDL_Rect destRect = {static_cast<int>(CELL_SIZE * x),
                         static_cast<int>(CELL_SIZE * y),
                         static_cast<int>(CELL_SIZE),
                         static_cast<int>(CELL_SIZE)};
    scc(SDL_RenderCopy(renderer, this->texture, srcRect, &destRect));
}

SDL_Rect* MapHandler::getSourceRect(int x, int y, MapType type){
    int posX = 0;
    int posY = 0;

    switch(type){
        case MapType::FOOD: {
            posX = 0;
            posY = TEXTURE_CELL_SIZE;
            break;
        }
        case MapType::BIG_FOOD: {
            posX = TEXTURE_CELL_SIZE;
            posY = TEXTURE_CELL_SIZE;
            break;
        }
        case MapType::DOOR: {
            posX = TEXTURE_CELL_SIZE * 2;
            posY = TEXTURE_CELL_SIZE;
            break;
        }
        case MapType::WALL: {
            if (y > 0 && y < this->map.size() - 1 && x > 0 && x < this->map[y].size() - 1 &&
                this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 15;

            else if (y > 0 && x > 0 && x < this->map[y].size() - 1 &&
                     this->map[y - 1][x] == 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 14;

            else if (y < this->map.size() - 1 && x > 0 && x < this->map[y].size() - 1 &&
                     this->map[y + 1][x] == 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 7;

            else if (y > 0 && x > 0 && y < this->map.size() - 1 &&
                     this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1 && this->map[y][x - 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 11;

            else if (y > 0 && y < this->map.size() - 1 && x < this->map[y].size() - 1 &&
                     this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 13;

            else if (y > 0 && y < this->map.size() - 1 && this->map[y - 1][x] == 1 && this->map[y + 1][x] == 1)
                    posX = TEXTURE_CELL_SIZE * 9;

            else if (x > 0 && x < this->map[y].size() - 1 && this->map[y][x - 1] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 6;

            else if (y < this->map[y].size() - 1 && x < this->map[y].size() - 1 && this->map[y + 1][x] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 5;

            else if (x > 0 && y < this->map.size() - 1 && this->map[y][x - 1] == 1 && this->map[y + 1][x] == 1)
                    posX = TEXTURE_CELL_SIZE * 3;

            else if (y > 0 && x < this->map[y].size() - 1 && this->map[y - 1][x] == 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 12;

            else if (y > 0 && x > 0 && this->map[y - 1][x] == 1 && this->map[y][x - 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 10;

            else if (y > 0 && this->map[y - 1][x] == 1)
                    posX = TEXTURE_CELL_SIZE * 8;

            else if (y < this->map.size() - 1 && this->map[y + 1][x] == 1)
                    posX = TEXTURE_CELL_SIZE * 1;

            else if (x > 0 && this->map[y][x - 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 2;

            else if (x < this->map[y].size() - 1 && this->map[y][x + 1] == 1)
                    posX = TEXTURE_CELL_SIZE * 4;
            
            break;
        }
    }

    return new SDL_Rect({posX, posY, TEXTURE_CELL_SIZE, TEXTURE_CELL_SIZE});
}