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
        enum MapType{
            WALL = 1,
            FOOD = 2,
            BIG_FOOD = 3,
            DOOR = 4
        } typedef MapType;

        typedef struct{
            int x;
            int y;
            SDL_Rect *rect;
            MapType type;
        } Element;

        MapHandler(class Game* game, std::string filename);
        ~MapHandler();
        void drawMap(SDL_Renderer* renderer);

        std::vector<Element *> elements;
    private:

        void createMapMatrix();
        void createElementsMatrix();

        void drawElement(SDL_Renderer *renderer, int x, int y, SDL_Rect *srcRect);
        SDL_Rect* getSourceRect(int x, int y, MapType type);

        std::vector< std::vector<int> > map;

        const std::string FILENAME; 
        SDL_Texture* texture;
        class Game* game;
};
#endif