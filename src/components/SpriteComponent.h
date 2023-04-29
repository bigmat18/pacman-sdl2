#pragma once
#include "Component.h"
#include <SDL2/SDL.h>

#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

class SpriteComponent : public Component {
    public:
        SpriteComponent(class Actor* owner, int drawOrder = 100);
        ~SpriteComponent();

        virtual void draw(SDL_Renderer* renderer);
        void setTexture(SDL_Texture* texture) { this->texture = texture; }
        void setActive(bool active) { this->active = active; }

        int getDrawOrder() const { return drawOrder; }
        int getTexHeight() const { return height; }
        int getTexWidth() const { return width; }

    protected:
        SDL_Texture* texture;
        SDL_Rect* sourceRect;
        int drawOrder;
        int width;
        int height;
        bool active;
};

#endif