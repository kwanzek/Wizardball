#include "TransformSystem.h"
#include <iostream>
#include <assert.h>

TransformSystem::TransformSystem()
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
    }
}

TransformSystem::~TransformSystem()
{
    //dtor
}

void TransformSystem::update(float deltaTime)
{}

TransformComponent& TransformSystem::addComponent( int eid, float x, float y, bool grounded )
{
    components.emplace_back(eid,x,y, grounded);
    handles[eid] = components.size()-1;
    return components[components.size()-1];
}

bool TransformSystem::deleteComponent( int eid)
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

bool TransformSystem::hasComponent( int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

TransformComponent& TransformSystem::getComponent( int eid)
{
    assert(eid < handles.capacity()&& this->hasComponent(eid));
    return components[handles[eid]];
}
