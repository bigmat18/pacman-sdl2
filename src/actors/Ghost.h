#pragma once
#include "Actor.h"

class Ghost : public Actor {
    public:
        Ghost(class Game* game);
        void updateActor(float deltaTime) override;

    private:
        void addAnimSpriteComponent(const char *fileName, const int heigth, const int width);

        void updatePosition(float deltaTime);

        enum Diraction {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            IDLE
        } typedef Diraction;

        Diraction currentDiraction;
        std::vector < class AnimSpriteComponent*> animations;
};