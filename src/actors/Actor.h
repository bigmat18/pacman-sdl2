#pragma once
#include "../Global.h"
#include <vector>

#ifndef ACTOR_H
#define ACTOR_H

class Actor {
    public:
        Actor(class Game* game);
        virtual ~Actor();
        void update(float deltaTime);

        void addComponent(class Component* component);
        void removeComponent(class Component* component);

        void updateComponents(float deltaTime);
        virtual void updateActor(float deltaTime);

        const Vector2D getPosition() const { return position; }
        void setPosition(const Vector2D pos) { position = pos; }

        class Game* getGame() { return game; }

        void setRotation(int rotation) { if(rotation <= 360 && rotation >= 0) this->rotation = rotation; } 
        int getRotation() const { return this->rotation; }

    protected:
        Vector2D position;
        std::vector<class Component*> components;
        class Game* game;
        int rotation;
};

#endif
