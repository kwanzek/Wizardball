#include "MovementSystem.h"
#include <unordered_map>
#include <iterator>

MovementSystem::MovementSystem()
{
    //ctor
}

MovementSystem::MovementSystem(ComponentManager* componentManager)
{
    this->componentManager = componentManager;
}

MovementSystem::~MovementSystem()
{
    //dtor
}

void MovementSystem::update(float deltaTime)
{
    for (std::unordered_map<unsigned int, VelocityComponent*>::iterator iter = componentManager->velocityComponents.begin();
        iter != componentManager->velocityComponents.end(); iter++)
    {
        int entityID = iter->first;
        VelocityComponent* velocityComponent = iter->second;

        std::unordered_map<unsigned int, TransformComponent*>::iterator it = componentManager->transformComponents.find(entityID);
        if (it != componentManager->transformComponents.end())
        {
            TransformComponent* transformComponent = it->second;
            transformComponent->x += velocityComponent->dx * deltaTime;
            transformComponent->y += velocityComponent->dy * deltaTime;
        }
    }
}
