#include "CollisionSystem.h"

#include <unordered_map>
#include <cmath>
#include <iostream>

CollisionSystem::CollisionSystem()
{
    //ctor
}

CollisionSystem::CollisionSystem(ComponentManager* componentManager) :
    componentManager(componentManager)
{

}

CollisionSystem::~CollisionSystem()
{
    //dtor
}

void CollisionSystem::update(float deltaTime)
{
    for (std::unordered_map<unsigned int, CollisionComponent*>::iterator iter = componentManager->collisionComponents.begin();
        iter != componentManager->collisionComponents.end(); iter++)
    {
        int entityID = iter->first;
        CollisionComponent* collisionComponent = iter->second;
        if (collisionComponent->layer == CollisionLayer::PLAYER)
        {
            //Need to get the velocity and transform components

            TransformComponent* transformComponent;
            std::unordered_map<unsigned int, TransformComponent*>::iterator it = componentManager->transformComponents.find(entityID);
            if (it != componentManager->transformComponents.end())
            {
                transformComponent = it->second;
            }

            VelocityComponent* velocityComponent;
            std::unordered_map<unsigned int, VelocityComponent*>::iterator velocityIt = componentManager->velocityComponents.find(entityID);
            if (velocityIt != componentManager->velocityComponents.end())
            {
                velocityComponent = velocityIt->second;
            }

            if (transformComponent == NULL || velocityComponent == NULL)
            {
                continue;
            }

            for (std::unordered_map<unsigned int, CollisionComponent*>::iterator otherIter = componentManager->collisionComponents.begin();
                otherIter != componentManager->collisionComponents.end(); otherIter++)
            {
                int otherEntityID = otherIter->first;
                CollisionComponent* otherCollision = otherIter->second;
                std::unordered_map<unsigned int, TransformComponent*>::iterator otherIt = componentManager->transformComponents.find(otherEntityID);
                TransformComponent* otherTransform;
                if (otherIt != componentManager->transformComponents.end())
                {
                    otherTransform = it->second;
                }

                if (otherCollision->layer == CollisionLayer::TILE && otherTransform != NULL)
                {
                    //Check bounding box collision, adding player dX and dY
                    Rectangle newPos = Rectangle(
                        collisionComponent->boundingBox.getLeft() + velocityComponent->dx,
                        collisionComponent->boundingBox.getTop() + velocityComponent->dy,
                        collisionComponent->boundingBox.getWidth(),
                        collisionComponent->boundingBox.getHeight()
                    );

                    if (newPos.collidesWith(otherCollision->boundingBox))
                    {
                        sides::Side collisionSide = newPos.getCollisionSide(otherCollision->boundingBox);
                        //We want to limit the entity's dy and dx based on which side the collision happened
                        //And how far we can go

                        if (collisionSide == sides::TOP)
                        {
                            velocityComponent->dy = std::min(static_cast<int>(velocityComponent->dy),
                                otherCollision->boundingBox.getBottom() - collisionComponent->boundingBox.getTop());
                        }
                        else if (collisionSide == sides::BOTTOM)
                        {
                            velocityComponent->dy = std::max(static_cast<int>(velocityComponent->dy),
                                otherCollision->boundingBox.getTop() - collisionComponent->boundingBox.getBottom());
                            transformComponent->grounded = true;
                        }
                        else if (collisionSide == sides::LEFT)
                        {
                            velocityComponent->dx = std::min(static_cast<int>(velocityComponent->dx),
                                otherCollision->boundingBox.getRight() - collisionComponent->boundingBox.getLeft()+1);
                        }
                        else if (collisionSide == sides::RIGHT)
                        {
                            velocityComponent->dx = std::max(static_cast<int>(velocityComponent->dx),
                                otherCollision->boundingBox.getLeft() - collisionComponent->boundingBox.getRight()-1);
                        }
                    }

                }

            }
        }


    }
}

