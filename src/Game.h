#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "MapHandler.h"

#ifndef GAME_H
#define GAME_H

class Game {
    public:
        Game();
        bool initialize();
        void runLoop();
        void shutdown();

        void addActor(class Actor *actor);
        void removeActor(class Actor *actor);

        void addSprite(class SpriteComponent *sprite);
        void removeSprite(class SpriteComponent *sprite);

        void loadData();
        void unloadData();
        SDL_Texture* getTexture(const std::string &fileName);

    private: 
        void processInput();
        void updateGame();
        void generateOutput();

        std::unordered_map<std::string, SDL_Texture*> textures;
        std::vector<class Actor*> actors;
        std::vector<class SpriteComponent*> sprites;
        
        MapHandler *map;
        SDL_Window *window;
        SDL_Renderer *renderer;
        Uint32 ticksCount;
        bool isRunning;
        class Pacman* pacman;
};

#endif
