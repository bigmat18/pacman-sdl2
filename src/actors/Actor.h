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

    private:
        void updateComponents(float deltaTime);
        virtual void updateActor(float deltaTime);

        Vector2D position;
        float scale;
        std::vector<class Component*> components;
        class Game* game;
};

#endif
