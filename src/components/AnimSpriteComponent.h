#pragma once
#include "SpriteComponent.h"
#include <vector>

#ifndef ANIM_SPRITE_COMPONENT_H
#define ANIM_SPRITE_COMPONENT_H

class AnimSpriteComponent : public SpriteComponent {
    public:
        AnimSpriteComponent(class Actor *owner, int drawOrder = 100);
        
        void update(float deltaTime) override;
        void setAnimRects(const std::vector<SDL_Rect*> &textures);
        float getAnimFPS() const { return animFPS; }
        void setAnimFPS(float fps) { animFPS = fps; }

    private:
        std::vector<SDL_Rect*> animRects;
        float currentFrame;
        float animFPS;
};

#endif