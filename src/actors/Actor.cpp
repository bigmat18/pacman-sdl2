#include "Actor.h"
#include "../Game.h"
#include "../Global.h"
#include "../components/Component.h"

Actor::Actor(Game *game) : position((Vector2D){0.0f, 0.0f}),
                           game(game),
                           rotation(0)
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


void Actor::addComponent(Component *component) {
    int myOrder = component->getUpdateOrder();
    auto iter = this->components.begin();
    for (;iter != this->components.end();++iter){
        if (myOrder < (*iter)->getUpdateOrder()){
            break;
        }
    }
    this->components.insert(iter, component);
}

void Actor::removeComponent(Component *component){
    auto iter = std::find(this->components.begin(), this->components.end(), component);
    if (iter != this->components.end()) this->components.erase(iter);
}
