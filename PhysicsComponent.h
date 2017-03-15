#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component
{
private:
    double movementSpeed;
    int destinationTile;
public:
    PhysicsComponent();
    virtual void update(GameEntity& gameEntity);
};

#endif // PHYSICS_COMPONENT_H