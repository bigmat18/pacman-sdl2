#include "SpriteComponent.h"
#include "../actors/Actor.h"
#include "../Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner),
                                                                texture(nullptr),
                                                                drawOrder(drawOrder),
                                                                width(100),
                                                                height(100)
{ ((Game*)owner->getGame())->addSprite(this); }

SpriteComponent::~SpriteComponent() { owner->getGame()->removeSprite(this); }