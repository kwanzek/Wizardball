#include "PlayerControlSystem.h"

#include <unordered_map>
#include <iterator>
#include <iostream>
#include <cmath>

PlayerControlSystem::PlayerControlSystem()
{
    //ctor
}

PlayerControlSystem::PlayerControlSystem(ComponentManager* componentManager, InputHandler* inputHandler) :
    componentManager(componentManager),
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

        if (velocityIt != componentManager->velocityComponents.end()
            && playerInputIt != componentManager->playerInputComponents.end()
            && transformIt != componentManager->transformComponents.end())
        {
            PlayerInputComponent* playerInputComponent = playerInputIt->second;
            VelocityComponent* velocityComponent = velocityIt->second;
            TransformComponent* transformComponent = transformIt->second;

            float targetDX = transformComponent->grounded ? velocityComponent->maxXSpeedGround : velocityComponent->maxXSpeedAir;
            if (inputHandler->isKeyHeld(playerInputComponent->leftCommand))
            {
                velocityComponent->dx = -1 * targetDX;
            }
            else if (inputHandler->isKeyHeld(playerInputComponent->rightCommand))
            {
                velocityComponent->dx = targetDX;
            }
            else
            {
                velocityComponent->dx = 0.0f;
            }

            if (velocityComponent->currentIgnoreGravityTime < 0)
            {
                velocityComponent->currentIgnoreGravityTime = 0;
            }
            else
            {
                velocityComponent->currentIgnoreGravityTime -= deltaTime;
            }

            if (transformComponent->grounded && velocityComponent->dy == 0 && inputHandler->wasKeyPressed(playerInputComponent->jumpCommand))
            {
                velocityComponent->dy = -1 * playerControllerComponent->jumpForce;
                velocityComponent->currentIgnoreGravityTime = velocityComponent->baseIgnoreGravityTime;
            }
        }

    }
}
