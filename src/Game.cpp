#include "Game.h"
#include "Global.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

Game::Game() : window(nullptr),
               renderer(nullptr),
               isRunning(true) {}

bool Game::Initialize() {
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

    LoadData();
    this->ticksCount = SDL_GetTicks();

    return true;
}

void Game::ShutDown() {
    UnloadData();
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    IMG_Quit();
    SDL_Quit();
}

void Game::RunLoop() {
    while (isRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
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

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

    std::cout << "FPS: " << 1.0f / deltaTime << std::endl;

    ticksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
        deltaTime = 0.05f;
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto sprite : sprites){
    }

    SDL_RenderPresent(renderer);
}

void Game::LoadData() {}

void Game::UnloadData() {}