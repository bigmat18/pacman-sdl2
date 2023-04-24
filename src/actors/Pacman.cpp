#include "Pacman.h"
#include "../Global.h"
#include "../components/AnimSpriteComponent.h"
#include "../Game.h"
#include <iostream>

Pacman::Pacman(Game *game) : Actor(game),
                             currentDiraction(Diraction::IDLE),
                             preDiraction(Diraction::IDLE)
{
    this->setPosition((Vector2D){CELL_SIZE * 9, CELL_SIZE * 15});

    AnimSpriteComponent *anim = new AnimSpriteComponent(this);
    anim->setTexture(this->game->getTexture("assets/Pacman16.png"));
    std::vector<SDL_Rect*> anims;

    for(int i = 0; i<6; i++)
        anims.push_back(new SDL_Rect({static_cast<int>(i * TEXTURE_CELL_SIZE), 0, 
                                      static_cast<int>(TEXTURE_CELL_SIZE), 
                                      static_cast<int>(TEXTURE_CELL_SIZE)}));

    anim->setAnimRects(anims);
}

void Pacman::updateActor(float deltaTime) {
    Actor::updateActor(deltaTime);
    this->updatePosition(deltaTime);
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

bool Pacman::hasCollision(Vector2D position){
    for(int i = 0; i<this->game->map->elements.size(); i++){
        if(this->game->map->elements[i]->type != 1) continue;

        if ((this->game->map->elements[i]->x * CELL_SIZE) < (position.x + CELL_SIZE) &&
            (this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE > position.x &&
            (this->game->map->elements[i]->y * CELL_SIZE) < (position.y + CELL_SIZE) &&
            (this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE > position.y){
            return true;
        }

        // if ((this->game->map->elements[i]->x * CELL_SIZE) <= position.x + CELL_SIZE &&
        //     ((this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE) >= position.x + CELL_SIZE &&
        //     (this->game->map->elements[i]->y * CELL_SIZE) <= position.y &&
        //     ((this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE) >= position.y){
        //     return true;
        // }

        // if((this->game->map->elements[i]->x * CELL_SIZE) <= position.x &&
        //    ((this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE) >= position.x &&
        //    (this->game->map->elements[i]->y * CELL_SIZE) <= position.y && 
        //    ((this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE) >= position.y){
        //     return true;
        // }

        // if((this->game->map->elements[i]->x * CELL_SIZE) <= position.x + CELL_SIZE &&
        //    ((this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE) >= position.x + CELL_SIZE &&
        //    (this->game->map->elements[i]->y * CELL_SIZE) <= position.y + CELL_SIZE && 
        //    ((this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE) >= position.y + CELL_SIZE){
        //     return true;
        // }

        // if((this->game->map->elements[i]->x * CELL_SIZE) <= position.x &&
        //    ((this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE) >= position.x &&
        //    (this->game->map->elements[i]->y * CELL_SIZE) <= position.y + CELL_SIZE && 
        //    ((this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE) >= position.y + CELL_SIZE){
        //     return true;
        // }
    }

    return false;
}

void Pacman::updatePosition(float deltaTime){
    Vector2D position = this->getPosition();


    switch (this->currentDiraction) {
        case Diraction::DOWN: {
            float y = position.y + (150.0f * deltaTime);

            if(!this->hasCollision((Vector2D){position.x, y})){
                position.y = y;
                this->setRotation(90);
                this->preDiraction = this->currentDiraction;
            } else {
                this->currentDiraction = this->preDiraction;
            }

            break;
        }
        case Diraction::UP: {
            float y = position.y - (150.0f * deltaTime);

            if (!this->hasCollision((Vector2D){position.x, y})){
                position.y = y;
                this->setRotation(270);
                this->preDiraction = this->currentDiraction;
            } else {
                this->currentDiraction = this->preDiraction;
            }
            break;
        }
        case Diraction::LEFT: {
            float x = position.x - (150.0f * deltaTime);

            if (!this->hasCollision((Vector2D){x, position.y})){
                position.x = x;
                this->setRotation(180);
                this->preDiraction = this->currentDiraction;
            } else {
                this->currentDiraction = this->preDiraction;
            }
            break;
        }
        case Diraction::RIGHT: {
            float x = position.x + (150.0f * deltaTime);

            if (!this->hasCollision((Vector2D){x, position.y})){
                position.x = x;
                this->setRotation(0);
                this->preDiraction = this->currentDiraction;
            } else {
                this->currentDiraction = this->preDiraction;
            }
            break;
        }
        default:
            break;
    }

    this->setPosition(position);
}