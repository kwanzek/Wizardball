#include "StateSystem.h"
#include <assert.h>

StateSystem::StateSystem()
{
    components.reserve(100);
    handles.reserve(100);
}

StateSystem::~StateSystem()
{
    //dtor
}

void StateSystem::update(float deltaTime)
{
}

StateComponent& StateSystem::addComponent(unsigned int eid, std::string stateString)
{
    components.emplace_back(eid, stateString);
    handles[eid] = components.size()-1;
    return components[components.size()-1];
}

bool StateSystem::deleteComponent(unsigned int eid)
{
    if (eid < handles.capacity())
    {
        unsigned int index = handles[eid];
        components[index] = components[components.size()-1];
        components.pop_back();
        handles[components[index].eid] = index;
        handles[eid] = -1;
        return true;
    }
    return false;
}

bool StateSystem::hasComponent(unsigned int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

StateComponent& StateSystem::getComponent(unsigned int eid)
{
    assert(eid < handles.capacity() && this->hasComponent(eid));
    return components[handles[eid]];
}
