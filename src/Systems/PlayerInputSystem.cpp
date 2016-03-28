#include "PlayerInputSystem.h"
#include <assert.h>

PlayerInputSystem::PlayerInputSystem()
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
    }
}

PlayerInputSystem::~PlayerInputSystem()
{
    //dtor
}

void PlayerInputSystem::update(float deltaTime)
{
}

PlayerInputComponent& PlayerInputSystem::addComponent(
    int eid,
    SDL_Scancode jump,
    SDL_Scancode left,
    SDL_Scancode right,
    SDL_Scancode fireball,
    SDL_Scancode pickup,
    SDL_JoystickID joystickID,
   int joyButtonJump,
   int joyButtonFireball,
   int joyButtonPickup
)
{
    components.push_back(PlayerInputComponent(
        eid,
        jump,
        left,
        right,
        fireball,
        pickup,
        joystickID,
        joyButtonJump,
        joyButtonFireball,
        joyButtonPickup
    ));

    handles[eid] = components.size()-1;
    return components.at(components.size()-1);
}

bool PlayerInputSystem::deleteComponent(int eid)
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

bool PlayerInputSystem::hasComponent(int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

PlayerInputComponent& PlayerInputSystem::getComponent(int eid)
{
    assert (eid < handles.capacity() && this->hasComponent(eid));
    return components[handles[eid]];
}
