#include "Component.h"
#include "../actors/Actor.h"

Component::Component(Actor* owner, int updateOrder) : owner(owner),
                                                      updateOrder(updateOrder)
{ owner->addComponent(this); }

Component::~Component() { this->owner->removeComponent(this); }

void Component::update(float deltaTime) {}