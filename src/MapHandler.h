#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

class MapHandler {
    public:
        MapHandler(class Game* game, std::string filename);
        void drawMap(SDL_Renderer* renderer);
    private:
        void createMap();
        void drawWall(SDL_Renderer *renderer, int x, int y, SDL_Color color);
        SDL_Rect getSourceRect(int x, int y);

        std::vector<std::vector<int>> map;
        const std::string FILENAME; 
        SDL_Texture *texture;
        Game* game;
};
#endif