#include "PlayerControlSystem.h"

#include <unordered_map>
#include <iterator>
#include <iostream>
#include <cmath>

PlayerControlSystem::PlayerControlSystem():
    System()
{
    //ctor
}

PlayerControlSystem::PlayerControlSystem(ComponentManager* componentManager, EntityFactory* entityFactory, InputHandler* inputHandler) :
    System(),
    componentManager(componentManager),
    entityFactory(entityFactory),
    inputHandler(inputHandler)
{

}

PlayerControlSystem::~PlayerControlSystem()
{
    //dtor
}

void PlayerControlSystem::update(float deltaTime)
{
    for (std::unordered_map<unsigned int, PlayerControllerComponent*>::iterator iter = componentManager->playerControllerComponents.begin();
        iter != componentManager->playerControllerComponents.end(); iter++)
    {
        int entityID = iter->first;
        PlayerControllerComponent* playerControllerComponent = iter->second;

        //Need to get VelocityComponent and PlayerInput to move the player if there is input
        std::unordered_map<unsigned int, VelocityComponent*>::iterator velocityIt = componentManager->velocityComponents.find(entityID);
        std::unordered_map<unsigned int, PlayerInputComponent*>::iterator playerInputIt = componentManager->playerInputComponents.find(entityID);
        std::unordered_map<unsigned int, TransformComponent*>::iterator transformIt = componentManager->transformComponents.find(entityID);
        std::unordered_map<unsigned int, StateComponent*>::iterator stateIt = componentManager->stateComponents.find(entityID);

        if (velocityIt != componentManager->velocityComponents.end()
            && playerInputIt != componentManager->playerInputComponents.end()
            && transformIt != componentManager->transformComponents.end()
            && stateIt != componentManager->stateComponents.end())
        {
            PlayerInputComponent* playerInputComponent = playerInputIt->second;
            VelocityComponent* velocityComponent = velocityIt->second;
            TransformComponent* transformComponent = transformIt->second;
            StateComponent* stateComponent = stateIt->second;

            float targetDX = transformComponent->grounded ? velocityComponent->maxXSpeedGround : velocityComponent->maxXSpeedAir;

            if (this->didAction(PlayerCommand::LEFT, *playerInputComponent))
            {
                velocityComponent->dx = -1 * targetDX;
                transformComponent->facing = Direction::Facing::LEFT;
                stateComponent->state = "run";
            }
            else if (this->didAction(PlayerCommand::RIGHT, *playerInputComponent))
            {
                velocityComponent->dx = targetDX;
                transformComponent->facing = Direction::Facing::RIGHT;
                stateComponent->state = "run";
            }
            else if (velocityComponent->dy == 0)
            {
                velocityComponent->dx = 0.0f;
                stateComponent->state = "idle";
            }
            velocityComponent->dx = targetDX;

            if (velocityComponent->currentIgnoreGravityTime <= 0 || !this->didAction(PlayerCommand::JUMP, *playerInputComponent))
            {
                velocityComponent->currentIgnoreGravityTime = 0;
                velocityComponent->ignoreGravity = false;
            }
            else if (velocityComponent->dy != 0)
            {
                velocityComponent->currentIgnoreGravityTime -= deltaTime;
            }

            if (transformComponent->grounded && velocityComponent->dy == 0 && this->didAction(PlayerCommand::JUMP, *playerInputComponent))
            {
                velocityComponent->dy = -1 * playerControllerComponent->jumpForce;
                velocityComponent->ignoreGravity = true;
                velocityComponent->currentIgnoreGravityTime = velocityComponent->baseIgnoreGravityTime;
            }

            if (this->didAction(PlayerCommand::FIREBALL, *playerInputComponent))
            {
                float fireballSpeed = 100;
                if (transformComponent->facing == Direction::Facing::LEFT)
                {
                    fireballSpeed *= -1;
                }
                entityFactory->createFireball(Vector2(transformComponent->x, transformComponent->y), fireballSpeed, 0);
            }

        }

    }
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
                || inputHandler->getJoyAxis(playerInputComponent.joystickID, Axis::XAXIS) < 0);
        case RIGHT:
            return (inputHandler->isKeyHeld(playerInputComponent.rightCommand)
                || inputHandler->getJoyAxis(playerInputComponent.joystickID, Axis::XAXIS) > 0);
        case FIREBALL:
            return (inputHandler->wasKeyPressed(playerInputComponent.fireballCommand)
                || inputHandler->wasJoyButtonPressed(playerInputComponent.joystickID, playerInputComponent.joyFireballButton));
        default:
            return false;
    }

}
