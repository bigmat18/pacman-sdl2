#include "Ghost.h"
#include "../Game.h"
#include "../Global.h"
#include "../components/AnimSpriteComponent.h"
#include "../actors/Pacman.h"

const unsigned int SIZE = 23;
const unsigned int HEIGTH = 144;

Ghost::Ghost(Game* game) : Actor(game),
                            currentDiraction(Diraction::IDLE)
{
    this->setPosition((Vector2D){CELL_SIZE * 8, CELL_SIZE * 9});

    this->addAnimSpriteComponent("assets/spritemap-384.png", 144, 0);
    this->addAnimSpriteComponent("assets/spritemap-384.png", 144, SIZE * 2);
    this->addAnimSpriteComponent("assets/spritemap-384.png", 144, SIZE * 4);
    this->addAnimSpriteComponent("assets/spritemap-384.png", 144, SIZE * 6);

    for(unsigned int i = 1; i < this->animations.size(); i++) this->animations[i]->setActive(false);
}

void Ghost::addAnimSpriteComponent(const char *fileName, const int heigth, const int width) {
    AnimSpriteComponent *anim = new AnimSpriteComponent(this);
    anim->setTexture(this->game->getTexture(fileName));
    std::vector<SDL_Rect *> anims;
    anims.push_back(new SDL_Rect({width, heigth, SIZE, SIZE}));
    anims.push_back(new SDL_Rect({width + (int)SIZE, heigth, SIZE, SIZE}));
    anim->setAnimRects(anims);
    this->animations.push_back(anim);
}

void Ghost::updateActor(float deltaTime){
    Actor::updateActor(deltaTime);
    this->updatePosition(deltaTime);
}

void Ghost::updatePosition(float deltaTime){
    Vector2D pacmanPosition = this->game->getPacman()->getPosition();
    Vector2D ghostPosition = this->getPosition();

    MapHandler* map = this->game->getMap();

    float x = floorf(ghostPosition.x) / CELL_SIZE;
    float y = floorf(ghostPosition.y) / CELL_SIZE;

    Diraction diraction = Diraction::IDLE;
    float max = -1.0f;

    if(map->getMap()[floorf(ghostPosition.y - CELL_SIZE) / CELL_SIZE][x] != 1 && this->currentDiraction != Diraction::DOWN) {
        float distance = pointDistance(pacmanPosition, (Vector2D){x * CELL_SIZE, floorf(ghostPosition.y - CELL_SIZE)});
        if(max < distance) max = distance; diraction = Diraction::UP;
    }

    if(map->getMap()[floorf(ghostPosition.y + CELL_SIZE) / CELL_SIZE][x] != 1 && this->currentDiraction != Diraction::UP) {
        float distance = pointDistance(pacmanPosition, (Vector2D){x * CELL_SIZE, floorf(ghostPosition.y + CELL_SIZE)});
        if(max < distance) max = distance; diraction = Diraction::DOWN;
    }

    if(map->getMap()[y][floorf(ghostPosition.x - CELL_SIZE) / CELL_SIZE] != 1 && this->currentDiraction != Diraction::RIGHT) {
        float distance = pointDistance(pacmanPosition, (Vector2D){floorf(ghostPosition.x - CELL_SIZE), y * CELL_SIZE});
        if(max < distance) max = distance; diraction = Diraction::LEFT;
    }

    if(map->getMap()[y][floorf(ghostPosition.x + CELL_SIZE) / CELL_SIZE] != 1 && this->currentDiraction != Diraction::LEFT) {
        float distance = pointDistance(pacmanPosition, (Vector2D){floorf(ghostPosition.x + CELL_SIZE), y * CELL_SIZE});
        if(max < distance) max = distance; diraction = Diraction::RIGHT;
    }

    switch (diraction) {
        case Diraction::UP: {
            float y = floorf(ghostPosition.y - (150.0f * deltaTime));
            y = ((int)y % 2) == 0 ? y : y + 2 - ((int)y % 2);

            ghostPosition.y = y;
            this->currentDiraction = diraction;
            break;
        }
        case Diraction::DOWN: {
            float y = floorf(ghostPosition.y + (150.0f * deltaTime));
            y = ((int)y % 2) == 0 ? y : y + 2 - ((int)y % 2);

            ghostPosition.y = y;
            this->currentDiraction = diraction;
            break;
        }
        case Diraction::LEFT: {
            float x = floorf(ghostPosition.x - (150.0f * deltaTime));
            x = ((int)x % 2) == 0 ? x : x + 2 - ((int)x % 2);

            ghostPosition.x = x;
            this->currentDiraction = diraction;
            break;
        }
        case Diraction::RIGHT: {
            float x = floorf(ghostPosition.x + (150.0f * deltaTime));
            x = ((int)x % 2) == 0 ? x : x + 2 - ((int)x % 2);

            ghostPosition.x = x;
            this->currentDiraction = diraction;
            break;
        }
        default: 
            break;
    }

    this->setPosition(ghostPosition);
}