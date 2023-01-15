#include <SDL2/SDL.h>

#ifndef GLOBAL_H
#define GLOBAL_H

#define BACKGROUND_COLOR           0x000000FF
#define MAP_COLOR                  0xFFFFFFFF

#define HEX_COLOR(hex)             \
        ((hex) >> (3 * 8)) & 0xFF, \
        ((hex) >> (2 * 8)) & 0xFF, \
        ((hex) >> (1 * 8)) & 0xFF, \
        ((hex) >> (0 * 8)) & 0xFF

const unsigned int SCALE                = 2;
const unsigned int NUM_ROW              = 21;
const unsigned int NUM_COMLUMN          = 19;
const unsigned int CELL_SIZE            = 16 * SCALE;
const unsigned int TEXTURE_CELL_SIZE    = 16;

constexpr int SCREEN_HEIGHT             = CELL_SIZE * NUM_ROW;
constexpr int SCREEN_WIDTH              = CELL_SIZE * NUM_COMLUMN;

constexpr int SCREEN_X_POS              = 100;
constexpr int SCREEN_Y_POS              = 100;

inline void scc(int code){
    if(code < 0){
        SDL_Log("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return;
}

inline void *scp(void *ptr){
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