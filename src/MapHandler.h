#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <string>
#include "Global.h"

#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

class MapHandler {
    public:
        MapHandler(class Game* game, std::string filename);
        ~MapHandler();
        void drawMap(SDL_Renderer* renderer);
    private:
        void createMapMatrix();
        void createRectsMatrix();
        void drawWall(SDL_Renderer *renderer, int x, int y, SDL_Color color);
        SDL_Rect* getSourceRect(int x, int y);

        std::vector< std::vector<int> > map;
        std::vector< std::vector<SDL_Rect *> > rects;
        const std::string FILENAME; 
        SDL_Texture *texture;
        Game* game;
};
#endif