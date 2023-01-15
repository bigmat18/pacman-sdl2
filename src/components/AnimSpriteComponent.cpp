#include "AnimSpriteComponent.h"
#include "../actors/Actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder) : SpriteComponent(owner, drawOrder),  
                                                                        currentFrame(0.0f),
                                                                        animFPS(20.0f) {}

void AnimSpriteComponent::update(float deltaTime) {

    if(this->animRects.size() > 0) {
        this->currentFrame += animFPS * deltaTime;

        while (this->currentFrame >= this->animRects.size())
            this->currentFrame -= this->animRects.size();

        this->sourceRect = this->animRects[static_cast<int>(this->currentFrame)];
        
    }
}

void AnimSpriteComponent::setAnimRects(const std::vector<SDL_Rect*> &rect) {
    this->animRects = rect;
    if(this->animRects.size() > 0) {
        this->currentFrame = 0.0f;
        this->sourceRect = this->animRects[0];
    }
}