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
    Vector2D position = this->game->getPacman()->getPosition();
    MapHandler* map = this->game->getMap();

    float x = floorf(this->getPosition().x) / CELL_SIZE;
    float y = floorf(this->getPosition().y) / CELL_SIZE;

    Diraction diraction = Diraction::IDLE;
    float max = -1.0f;

    if(map->getMap()[y-1][x] != 1) {
        float distance = pointDistance(position, (Vector2D){x * CELL_SIZE, y * CELL_SIZE});
        if(max < distance) {
            max = distance;
        }
    }

    if(map->getMap()[y+1][x] != 1) {
        float distance = pointDistance(position, (Vector2D){x * CELL_SIZE, y * CELL_SIZE});
        if(max < distance) max = distance;
    }

    if(map->getMap()[y][x-1] != 1) {
        float distance = pointDistance(position, (Vector2D){x * CELL_SIZE, y * CELL_SIZE});
        if(max < distance) max = distance;
    }

    if(map->getMap()[y-1][x+1] != 1) {
        float distance = pointDistance(position, (Vector2D){x * CELL_SIZE, y * CELL_SIZE});
        if(max < distance) max = distance;
    }
}