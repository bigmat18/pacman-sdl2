#pragma once
#include "Actor.h"

#ifndef PACMAN_H
#define PACMAN_H

class Pacman : public Actor {
    public:
        Pacman(class Game* game);
        void updateActor(float deltaTime) override;
        void proccessKeyboard(const uint8_t *state);

    private:
        enum Diraction {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            IDLE
        } typedef Diraction;

        void updatePosition(float deltaTime);
        int hasCollision(Vector2D position);

        Diraction currentDiraction;
        Diraction preDiraction;
};

#endif