#include "MovementSystem.h"
#include <unordered_map>
#include <iterator>
#include <math.h>
#include <cmath>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

MovementSystem::MovementSystem():
    System()
{
    components.reserve(100);
    handles.reserve(100);
    //components.emplace_back(0,0.f,0.f, 0.f, 0.f, 0.f);
}

MovementSystem::MovementSystem(TransformSystem* transformSystem):
    System(),
    transformSystem(transformSystem)
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
    }
}

MovementSystem::~MovementSystem()
{
    //dtor
}

void MovementSystem::update(float deltaTime)
{

    for (int i = 0; i < this->components.size(); ++i)
    {
        VelocityComponent& velocityComponent = components[i];
        if (!velocityComponent.enabled)
        {
            continue;
        }
        int entityID = velocityComponent.eid;
        if (transformSystem->hasComponent(entityID))
        {
            TransformComponent& transformComponent = transformSystem->getComponent(entityID);

            if (transformComponent.grounded && velocityComponent.xFriction > 0 && velocityComponent.dx != 0)
            {
                float oldDx = velocityComponent.dx;
                float newDx = abs(velocityComponent.dx) - velocityComponent.xFriction *  deltaTime;
                newDx = std::max(0.0f, newDx);
                if (oldDx < 0)
                {
                    newDx *= -1;
                }
                velocityComponent.dx = newDx;
            }

            if (!transformComponent.grounded && velocityComponent.dy < velocityComponent.maxYSpeed && !velocityComponent.ignoreGravity && !velocityComponent.currentIgnoreGravityTime > 0)
            {
                velocityComponent.dy += globals::GRAVITY * deltaTime;
            }

            transformComponent.x += (velocityComponent.dx * deltaTime);
            velocityComponent.dy = std::min(velocityComponent.dy, velocityComponent.maxYSpeed);
            transformComponent.y += velocityComponent.dy * deltaTime;
            transformComponent.y = (transformComponent.y);

        }
    }

}

VelocityComponent& MovementSystem::addComponent(int eid, float dx, float dy, float maxXSpeedGround, float maxXSpeedAir, float maxYSpeed, float xFriction, float baseIgnoreGravityTime, float currentIgnoreGravityTime, bool ignoreGravity)
{
    components.push_back(VelocityComponent(eid,dx,dy, maxXSpeedGround, maxXSpeedAir, maxYSpeed, xFriction, baseIgnoreGravityTime, currentIgnoreGravityTime, ignoreGravity));
    handles[eid] = components.size()-1;
    return components[components.size()-1];
}

bool MovementSystem::deleteComponent(int eid)
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

bool MovementSystem::hasComponent(int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

VelocityComponent& MovementSystem::getComponent(int eid)
{
    assert(eid < handles.capacity() && this->hasComponent(eid));
    return components[handles[eid]];
}
