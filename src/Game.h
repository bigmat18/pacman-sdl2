#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

#ifndef GAME_H
#define GAME_H

class Game {
    public:
        Game();
        bool Inizialise();
        void RunLoop();
        void ShutDown();

        void AddActor(class Actor *actor);
        void RemoveActor(class Actor *actor);

        void AddSprite(class SpriteComponent *sprite);
        void RemoveSprite(class SpriteComponent *sprite);

        void LoadData();
        void UnloadData();

    private:
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();

        std::unordered_map<std::string, SDL_Texture *> textures;
        std::vector<class Actor*> actors;
        std::vector<class SpriteComponent*> sprites;

        SDL_Window *window;
        SDL_Renderer *renderer;
        Uint32 ticksCount;
        bool isRunning;
};

#endif
