#include "Pacman.h"
#include "../Global.h"

Pacman::Pacman(Game *game) : Actor(game),
                             currentDiraction(Diraction::IDLE) 
{
    this->setPosition((Vector2D){CELL_SIZE * 9, CELL_SIZE * 15});
}

void Pacman::updateActor(float deltaTime) {
    Actor::updateActor(deltaTime);
    Vector2D position = this->getPosition();

    switch (this->currentDiraction) {
        case Diraction::DOWN: {
            break;
        }
        case Diraction::UP: {
            break;
        }
        case Diraction::LEFT: {
            break;
        }
        case Diraction::RIGHT: {
            break;
        }
        default:
            break;
    }

    this->setPosition(position);
}

void Pacman::proccessKeyboard(const uint8_t *state){
    if (state[SDL_SCANCODE_D]) 
        this->currentDiraction = Diraction::RIGHT;
    if (state[SDL_SCANCODE_A]) 
        this->currentDiraction = Diraction::LEFT;
    if (state[SDL_SCANCODE_S]) 
        this->currentDiraction = Diraction::DOWN;
    if (state[SDL_SCANCODE_W]) 
        this->currentDiraction = Diraction::UP;
}