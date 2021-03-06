#include "PlayerControlSystem.h"

#include <unordered_map>
#include <iterator>
#include <iostream>
#include <cmath>
#include <assert.h>

PlayerControlSystem::PlayerControlSystem():
    System()
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
    }
}

PlayerControlSystem::PlayerControlSystem(
    InputHandler* inputHandler,
    TransformSystem* ts,
    MovementSystem* ms,
    StateSystem* ss,
    PlayerInputSystem* pis,
    PickupSystem* pickupSys
) :
    System(),
    inputHandler(inputHandler),
    transformSystem(ts),
    movementSystem(ms),
    stateSystem(ss),
    playerInputSystem(pis),
    pickupSystem(pickupSys)
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles[i] = -1;
    }
}

PlayerControlSystem::~PlayerControlSystem()
{
    //dtor
}

void PlayerControlSystem::update(float deltaTime)
{

    for (unsigned int i = 0; i < components.size(); ++i)
    {
        PlayerControllerComponent& playerControllerComponent = components[i];
        int eid = playerControllerComponent.eid;
        playerControllerComponent.threwBall = false;
        if ( transformSystem->hasComponent(eid)
               && movementSystem->hasComponent(eid)
               && playerInputSystem->hasComponent(eid)
               && stateSystem->hasComponent(eid) )
        {
            TransformComponent& transformComponent = transformSystem->getComponent(eid);
            VelocityComponent& velocityComponent = movementSystem->getComponent(eid);
            PlayerInputComponent& playerInputComponent = playerInputSystem->getComponent(eid);
            StateComponent& stateComponent = stateSystem->getComponent(eid);

            float targetDX = transformComponent.grounded ? velocityComponent.maxXSpeedGround : velocityComponent.maxXSpeedAir;

            if (this->didAction(PlayerCommand::LEFT, playerInputComponent))
            {
                velocityComponent.dx = -1 * targetDX;
                transformComponent.facing = Direction::Facing::LEFT;
                stateComponent.state = "run";
            }
            else if (this->didAction(PlayerCommand::RIGHT, playerInputComponent))
            {
                velocityComponent.dx = targetDX;
                transformComponent.facing = Direction::Facing::RIGHT;
                stateComponent.state = "run";
            }
            else
            {
                velocityComponent.dx = 0.0f;
                stateComponent.state = "idle";
            }

            if (velocityComponent.currentIgnoreGravityTime <= 0 || !this->didAction(PlayerCommand::JUMP, playerInputComponent))
            {
                velocityComponent.currentIgnoreGravityTime = 0;
                velocityComponent.ignoreGravity = false;
            }
            else if (velocityComponent.dy != 0)
            {
                velocityComponent.currentIgnoreGravityTime -= deltaTime;
            }

            if (transformComponent.grounded && velocityComponent.dy == 0 && this->didAction(PlayerCommand::JUMP, playerInputComponent))
            {
                velocityComponent.dy = -1 * playerControllerComponent.jumpForce;
                velocityComponent.ignoreGravity = true;
                velocityComponent.currentIgnoreGravityTime = velocityComponent.baseIgnoreGravityTime;
                transformComponent.grounded = false;
            }

            if (this->didAction(PlayerCommand::FIREBALL, playerInputComponent))
            {
                float fireballSpeed = 100;
                if (transformComponent.facing == Direction::Facing::LEFT)
                {
                    fireballSpeed *= -1;
                }
                entityFactory->createFireball(Vector2(transformComponent.x, transformComponent.y), fireballSpeed, 0);
            }

            if (this->didAction(PlayerCommand::PICKUP, playerInputComponent) && pickupSystem->hasComponent(eid))
            {
                PickupComponent &pickupComponent = pickupSystem->getComponent(eid);
                pickupSystem->throwBall(eid, pickupComponent.otherEID);
                playerControllerComponent.threwBall = true;
            }
        }
    }
}

PlayerControllerComponent& PlayerControlSystem::addComponent(int eid)
{
    components.push_back(PlayerControllerComponent(eid));
    handles[eid] = components.size()-1;
    return components.at(components.size()-1);
}

bool PlayerControlSystem::deleteComponent(int eid)
{
    if (eid < handles.capacity() && this->hasComponent(eid))
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

bool PlayerControlSystem::hasComponent(int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

PlayerControllerComponent& PlayerControlSystem::getComponent(int eid)
{
    assert (eid < handles.capacity() && this->hasComponent(eid));
    return components[handles[eid]];
}

bool PlayerControlSystem::didAction(PlayerCommand playerCommand, PlayerInputComponent& playerInputComponent)
{
    switch(playerCommand)
    {
        case JUMP:
            return (inputHandler->isKeyHeld(playerInputComponent.jumpCommand)
                || inputHandler->isJoyButtonHeld(playerInputComponent.joystickID, playerInputComponent.joyJumpButton));
        case LEFT:
            return (inputHandler->isKeyHeld(playerInputComponent.leftCommand)
                || inputHandler->getJoyAxis(playerInputComponent.joystickID, Axis::X) < 0);
        case RIGHT:
            return (inputHandler->isKeyHeld(playerInputComponent.rightCommand)
                || inputHandler->getJoyAxis(playerInputComponent.joystickID, Axis::X) > 0);
        case FIREBALL:
            return (inputHandler->wasKeyPressed(playerInputComponent.fireballCommand)
                || inputHandler->wasJoyButtonPressed(playerInputComponent.joystickID, playerInputComponent.joyFireballButton));
        case PICKUP:
            return (inputHandler->wasKeyPressed(playerInputComponent.pickupCommand)
                || inputHandler->wasJoyButtonPressed(playerInputComponent.joystickID, playerInputComponent.joyPickupButton));
        default:
            return false;
    }

}

void PlayerControlSystem::handleBallCollision(int eid, int otherEID)
{
    if (playerInputSystem->hasComponent(eid) && this->hasComponent(eid))
    {
        PlayerInputComponent& playerInputComponent = playerInputSystem->getComponent(eid);
        PlayerControllerComponent& playerControllerComponent = this->getComponent(eid);
        if (this->didAction(PlayerCommand::PICKUP, playerInputComponent) && !playerControllerComponent.threwBall)
        {
            pickupSystem->pickupBall(eid, otherEID);
        }
    }
}
