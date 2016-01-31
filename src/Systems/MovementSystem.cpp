#include "MovementSystem.h"
#include <unordered_map>
#include <iterator>
#include <math.h>

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
            if (!transformComponent->grounded && velocityComponent->dy < velocityComponent->maxYSpeed && velocityComponent->currentIgnoreGravityTime <= 0)
            {
                velocityComponent->dy += globals::GRAVITY * deltaTime;
            }
            velocityComponent->dy = std::min(velocityComponent->dy, velocityComponent->maxYSpeed);
            transformComponent->y += velocityComponent->dy * deltaTime;

            std::unordered_map<unsigned int, CollisionComponent*>::iterator collisionIt = componentManager->collisionComponents.find(entityID);
            if (collisionIt != componentManager->collisionComponents.end())
            {
                CollisionComponent* collisionComponent = collisionIt->second;
                collisionComponent->boundingBox.x = ceil(transformComponent->x);
                collisionComponent->boundingBox.y = ceil(transformComponent->y);
            }
        }


    }
}
