#include "PickupSystem.h"

#include <assert.h>
#include <iostream>

PickupSystem::PickupSystem()
{
    //ctor
}

PickupSystem::PickupSystem(TransformSystem* transformSystem, MovementSystem* movementSystem):
    transformSystem(transformSystem),
    movementSystem(movementSystem)
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
    }
}

PickupSystem::~PickupSystem()
{
    //dtor
}

void PickupSystem::update(float deltaTime)
{
    for (int i = 0; i < components.size(); ++i)
    {
        PickupComponent& pickupComponent = components[i];
        if (transformSystem->hasComponent(pickupComponent.eid) && transformSystem->hasComponent(pickupComponent.otherEID))
        {
            TransformComponent& transformComponent = transformSystem->getComponent(pickupComponent.eid);
            TransformComponent& otherTransform = transformSystem->getComponent(pickupComponent.otherEID);
            otherTransform.x = transformComponent.x;
            otherTransform.y = transformComponent.y;
        }
    }
}

PickupComponent& PickupSystem::addComponent(int eid, int otherEID)
{
    components.emplace_back(eid,otherEID);
    handles[eid] = components.size()-1;
    return components[components.size()-1];
}

bool PickupSystem::deleteComponent(int eid)
{
    if (eid < handles.capacity())
    {
        int index = handles[eid];
        components[index] = components[components.size()-1];
        components.pop_back();
        handles[components[index].eid] = index;
        handles[eid] = -1;
        return true;
    }
    return false;
}

bool PickupSystem::hasComponent(int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

PickupComponent& PickupSystem::getComponent(int eid)
{
    assert (eid < handles.size() && this->hasComponent(eid));
    return components[handles[eid]];
}

void PickupSystem::throwBall(int eid, int otherEID)
{
    if (collisionSystem->hasComponent(otherEID) && movementSystem->hasComponent(otherEID) && transformSystem->hasComponent(eid))
    {
        CollisionComponent& otherCollision = collisionSystem->getComponent(otherEID);
        VelocityComponent& otherVelocity = movementSystem->getComponent(otherEID);
        TransformComponent& transformComponent = transformSystem->getComponent(eid);
        otherCollision.enabled = true;
        otherVelocity.enabled = true;
        int facing = transformComponent.facing == Direction::LEFT ? -1 : 1;
        otherVelocity.dy = -300;
        otherVelocity.dx = 100*facing;
        this->deleteComponent(eid);
    }
}

void PickupSystem::pickupBall(int eid, int otherEID)
{
    if (collisionSystem->hasComponent(otherEID) && movementSystem->hasComponent(otherEID))
    {
        CollisionComponent& otherCollision = collisionSystem->getComponent(otherEID);
        VelocityComponent& otherVelocity = movementSystem->getComponent(otherEID);
        otherCollision.enabled = false;
        otherVelocity.enabled = false;
    }
    this->addComponent(eid, otherEID);
}
