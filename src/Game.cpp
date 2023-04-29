#include "Game.h"
#include "Global.h"
#include "MapHandler.h"
#include "actors/Actor.h"
#include "actors/Pacman.h"
#include "actors/Ghost.h"
#include "components/SpriteComponent.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

Game::Game() : window(nullptr),
               renderer(nullptr),
               isRunning(true), 
               map(nullptr) {}

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
    this->pacman->proccessKeyboard(state);
}

void Game::updateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

    std::cout << "FPS: " << 1.0f / deltaTime << std::endl;

    ticksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
        deltaTime = 0.05f;

    for (auto actor : this->actors){
        actor->update(deltaTime);
    }
}

void Game::generateOutput() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    this->map->drawMap(renderer);

    for(auto sprite : this->sprites) 
        sprite->draw(this->renderer);

    SDL_RenderPresent(renderer);
}

void Game::loadData() {
    this->map = new MapHandler(this, "map.txt");
    this->pacman = new Pacman(this);
    new Ghost(this);
}

void Game::unloadData() {
    delete this->map;
}

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

void Game::addSprite(SpriteComponent* sprite){
    int drawOrder = sprite->getDrawOrder();
    auto iter = sprites.begin();
    for (;iter != sprites.end(); ++iter){
        if (drawOrder < (*iter)->getDrawOrder()){
            break;
        }
    }
    this->sprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent *sprite){
    auto iter = std::find(this->sprites.begin(), this->sprites.end(), sprite);
    this->sprites.erase(iter);
}