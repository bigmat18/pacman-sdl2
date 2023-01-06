#include <SDL2/SDL.h>

#ifndef GLOBAL_H
#define GLOBAL_H

constexpr int SCREEN_HEIGHT = 768;
constexpr int SCREEN_WIDTH  = 1024;

constexpr int SCREEN_X_POS  = 100;
constexpr int SCREEN_Y_POS  = 100;

void scc(int code){
    if(code < 0){
        SDL_Log("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return;
}

void *scp(void *ptr){
    if(ptr == NULL){
        SDL_Log("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return ptr;
}

typedef struct {
    float x;
    float y;
} Vector2D;

#endif