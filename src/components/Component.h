#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
    public:
        Component(class Actor* owner, int updateOrder = 100);
        virtual ~Component();
        virtual void update(float deltaTime);
        
    protected:
        class Actor* owner;
        int updateOrder;

};

#endif