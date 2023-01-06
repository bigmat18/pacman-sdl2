#include "Actor.h"
#include "../Game.h"
#include "../Global.h"
#include "../components/Component.h"

Actor::Actor(Game* game): position((Vector2D){0.0f, 0.0f}),
                          scale(1.0f),
                          game(game)
{game->addActor(this);}


Actor::~Actor() {
    game->removeActor(this);
    while(!components.empty()) 
        delete components.back();
}

void Actor::update(float deltaTime) {
    updateComponents(deltaTime);
    updateActor(deltaTime);
}

void Actor::updateComponents(float deltaTime) {
    for(auto component : this->components){
        component->update(deltaTime);
    }
}

void Actor::updateActor(float deltaTime) {}


