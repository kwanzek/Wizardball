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

            if (inputHandler->isKeyHeld(playerInputComponent->leftCommand))
            {
                velocityComponent->dx = -1 * targetDX;
                transformComponent->facing = Direction::Facing::LEFT;
                stateComponent->state = "run";
            }
            else if (inputHandler->isKeyHeld(playerInputComponent->rightCommand))
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

            if (velocityComponent->currentIgnoreGravityTime <= 0 || !inputHandler->isKeyHeld(playerInputComponent->jumpCommand))
            {
                velocityComponent->currentIgnoreGravityTime = 0;
                velocityComponent->ignoreGravity = false;
            }
            else if (velocityComponent->dy != 0)
            {
                velocityComponent->currentIgnoreGravityTime -= deltaTime;
            }

            if (transformComponent->grounded && velocityComponent->dy == 0 && inputHandler->wasKeyPressed(playerInputComponent->jumpCommand))
            {
                velocityComponent->dy = -1 * playerControllerComponent->jumpForce;
                velocityComponent->ignoreGravity = true;
                velocityComponent->currentIgnoreGravityTime = velocityComponent->baseIgnoreGravityTime;
            }

            if (inputHandler->wasKeyPressed(playerInputComponent->fireballCommand))
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
