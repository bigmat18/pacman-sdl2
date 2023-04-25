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

int Pacman::hasCollision(Vector2D position){
    int indexFood = -1;

    for(int i = 0; i<this->game->map->elements.size(); i++){

        if (this->game->map->elements[i]->type == 1 &&
            (this->game->map->elements[i]->x * CELL_SIZE) < (position.x + CELL_SIZE) &&
            (this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE > position.x &&
            (this->game->map->elements[i]->y * CELL_SIZE) < (position.y + CELL_SIZE) &&
            (this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE > position.y) {

            if(indexFood != -1) this->game->map->elements.erase(std::next(this->game->map->elements.begin(), indexFood));
            return i;
        }

        if ((this->game->map->elements[i]->type == 2 || this->game->map->elements[i]->type == 3) &&
            ((this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE / 4) < (position.x + CELL_SIZE) &&
            ((this->game->map->elements[i]->x * CELL_SIZE) + CELL_SIZE / 4) + CELL_SIZE / 2 > position.x &&
            ((this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE / 4) < (position.y + CELL_SIZE) &&
            ((this->game->map->elements[i]->y * CELL_SIZE) + CELL_SIZE / 4) + CELL_SIZE / 2 > position.y){
            indexFood = i;
        }
    }
    if (indexFood != -1)
        this->game->map->elements.erase(std::next(this->game->map->elements.begin(), indexFood));

    return -1;
}

void Pacman::updatePosition(float deltaTime){
    Vector2D position = this->getPosition();


    switch (this->currentDiraction) {
        case Diraction::DOWN: {
            float y = floorf(position.y + (150.0f * deltaTime));
            y = ((int)y % 2) == 0 ? y : y + 2 - ((int)y % 2);

            int index = this->hasCollision((Vector2D){position.x, y});
            Vector2D collision;
            if (index != -1) collision = (Vector2D){static_cast<float>(this->game->map->elements[index]->x * CELL_SIZE),
                                                    static_cast<float>(this->game->map->elements[index]->y * CELL_SIZE)};

            if(index == -1){
                position.y = y;
                this->setRotation(90);
                this->preDiraction = this->currentDiraction;
            } else if (currentDiraction == preDiraction){
                position.y += collision.y - (position.y + CELL_SIZE);
            } else {
                this->currentDiraction = this->preDiraction;
                this->updatePosition(deltaTime);
                return;
            }

            break;
        }
        case Diraction::UP: {
            float y = floorf(position.y - (150.0f * deltaTime));

            y = ((int)y % 2) == 0 ? y : y + 2 - ((int)y % 2);

            int index = this->hasCollision((Vector2D){position.x, y});
            Vector2D collision;
            if (index != -1) collision = (Vector2D){static_cast<float>(this->game->map->elements[index]->x * CELL_SIZE),
                                                    static_cast<float>(this->game->map->elements[index]->y * CELL_SIZE)};

            if (index == -1){
                position.y = y;
                this->setRotation(270);
                this->preDiraction = this->currentDiraction;
            } else if (currentDiraction == preDiraction){
                position.y -= position.y - (collision.y + CELL_SIZE);
            } else {
                this->currentDiraction = this->preDiraction;
                this->updatePosition(deltaTime);
                return;
            }

            break;
        }
        case Diraction::LEFT: {
            float x = floorf(position.x - (150.0f * deltaTime));

            x = ((int)x % 2) == 0 ? x : x + 2 - ((int)x % 2);

            int index = this->hasCollision((Vector2D){x, position.y});
            Vector2D collision;
            if (index != -1) collision = (Vector2D){static_cast<float>(this->game->map->elements[index]->x * CELL_SIZE),
                                                    static_cast<float>(this->game->map->elements[index]->y * CELL_SIZE)};

            if (index == -1){
                if(x <= 0) position.x = SCREEN_WIDTH;
                else position.x = x;

                this->setRotation(180);
                this->preDiraction = this->currentDiraction;
            } else if (currentDiraction == preDiraction){
                position.x -= position.x - (collision.x + CELL_SIZE);
            } else {
                this->currentDiraction = this->preDiraction;
                this->updatePosition(deltaTime);
                return;
            }

            break;
        }
        case Diraction::RIGHT: {
            float x = floorf(position.x + (150.0f * deltaTime));

            x = ((int)x % 2) == 0 ? x : x + 2 - ((int)x % 2);

            int index = this->hasCollision((Vector2D){x, position.y});

            Vector2D collision;
            if (index != -1) collision = (Vector2D){static_cast<float>(this->game->map->elements[index]->x * CELL_SIZE),
                                                    static_cast<float>(this->game->map->elements[index]->y * CELL_SIZE)};

            if (index == -1){
                if(x >= SCREEN_WIDTH) position.x = 0;
                else position.x = x;

                this->setRotation(0);
                this->preDiraction = this->currentDiraction;
            } else if (currentDiraction == preDiraction){
                position.x += collision.x - (position.x + CELL_SIZE);
            } else {
                this->currentDiraction = this->preDiraction;
                this->updatePosition(deltaTime);
                return;
            }

            break;
        }
        default:
            break;
    }

    this->setPosition(position);
}