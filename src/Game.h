#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

#ifndef GAME_H
#define GAME_H

class Game {
    public:
        Game(std::vector<std::vector<int>> *map);
        bool initialize();
        void runLoop();
        void shutdown();

        void addActor(class Actor *actor);
        void removeActor(class Actor *actor);

        void addSprite(class SpriteComponent *sprite);
        void removeSprite(class SpriteComponent *sprite);

        void loadData();
        void unloadData();

    private:
        void processInput();
        void updateGame();
        void generateOutput();

        std::unordered_map<std::string, SDL_Texture*> textures;
        std::vector<class Actor*> actors;
        std::vector<class SpriteComponent*> sprites;
        const std::vector<std::vector<int>>* MAP;

        SDL_Window *window;
        SDL_Renderer *renderer;
        Uint32 ticksCount;
        bool isRunning;
};

#endif
