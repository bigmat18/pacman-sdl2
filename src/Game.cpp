#include "Game.h"
#include "Global.h"
#include "MapHandler.h"
#include "actors/Actor.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

Game::Game() : map(nullptr),
               window(nullptr),
               renderer(nullptr),
               isRunning(true) {}

bool Game::initialize() {
    scc(SDL_Init(SDL_INIT_VIDEO));
    this->window = (SDL_Window*)scp(SDL_CreateWindow("Pacman",
                                                     SCREEN_X_POS,
                                                     SCREEN_Y_POS,
                                                     SCREEN_WIDTH,
                                                     SCREEN_HEIGHT,
                                                     SDL_WINDOW_RESIZABLE));

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((initStatus & flags) != flags) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    this->loadData();
    this->ticksCount = SDL_GetTicks();

    return true;
}

void Game::shutdown(){
    this->unloadData();
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    IMG_Quit();
    SDL_Quit();
}

void Game::runLoop() {
    while (isRunning) {
        this->processInput();
        this->updateGame();
        this->generateOutput();
    }
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) isRunning = false;
}

void Game::updateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

    std::cout << "FPS: " << 1.0f / deltaTime << std::endl;

    ticksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
        deltaTime = 0.05f;
}

void Game::generateOutput() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    this->map->drawMap(renderer);
    // SDL_Rect src = {0, 0, 16, 16};
    // SDL_Rect dest = {0, 0, (int)(CELL_SIZE / 2), (int)(CELL_SIZE / 2)};

    // SDL_Texture* texture = this->getTexture("assets/Map16.png");

    // SDL_RenderCopy(renderer, 
    //                texture,
    //                &src,
    //                &dest);

    for (auto sprite : sprites){
    }

    SDL_RenderPresent(renderer);
}

void Game::loadData() {
    this->map = new MapHandler(this, "map.txt");
}

void Game::unloadData() {}

void Game::addActor(Actor* actor) {
    this->actors.emplace_back(actor);
}

void Game::removeActor(Actor* actor) {
    auto iterator = std::find(this->actors.begin(), this->actors.end(), actor);
    if(iterator != actors.end()) {
        std::iter_swap(iterator, actors.end() - 1);
        actors.pop_back();
    }
}

SDL_Texture *Game::getTexture(const std::string &fileName){
    SDL_Texture* texture = nullptr;
    auto iter = this->textures.find(fileName);

    if (iter != this->textures.end()) texture = iter->second;
    else {
        SDL_Surface *surf = (SDL_Surface*)scp(IMG_Load(fileName.c_str()));

        if(!surf) return nullptr;

        texture = (SDL_Texture*)scp(SDL_CreateTextureFromSurface(renderer, surf));
        if (!texture) return nullptr;

        SDL_FreeSurface(surf);
        this->textures.emplace(fileName.c_str(), texture);
    }
    return texture;
}