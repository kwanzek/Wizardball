#include "CollisionSystem.h"

#include <unordered_map>
#include <cmath>
#include <iostream>

CollisionSystem::CollisionSystem():
    System()
{
    //ctor
}

CollisionSystem::CollisionSystem(ComponentManager* componentManager) :
    System(),
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

        //Need to get the velocity and transform components
        TransformComponent* transformComponent = NULL;
        bool hasGroundedCollision = false;
        std::unordered_map<unsigned int, TransformComponent*>::iterator it = componentManager->transformComponents.find(entityID);
        if (it != componentManager->transformComponents.end())
        {
            transformComponent = it->second;
        }
        else
        {
            continue;
        }

        VelocityComponent* velocityComponent = NULL;
        std::unordered_map<unsigned int, VelocityComponent*>::iterator velocityIt = componentManager->velocityComponents.find(entityID);
        if (velocityIt != componentManager->velocityComponents.end())
        {
            velocityComponent = velocityIt->second;
        }
        else
        {
            continue;
        }

        //Check bounding box collision, adding player dX and dY
        Rectangle newPos = Rectangle(
            collisionComponent->boundingBox.getLeft() + velocityComponent->dx * deltaTime,
            collisionComponent->boundingBox.getTop() + velocityComponent->dy * deltaTime,
            collisionComponent->boundingBox.getWidth(),
            collisionComponent->boundingBox.getHeight()
        );

        for (std::unordered_map<unsigned int, CollisionComponent*>::iterator otherIter = componentManager->collisionComponents.begin();
            otherIter != componentManager->collisionComponents.end(); otherIter++)
        {
            int otherEntityID = otherIter->first;
            if (entityID == otherEntityID)
            {
                continue;
            }
            CollisionComponent* otherCollision = otherIter->second;
            std::unordered_map<unsigned int, TransformComponent*>::iterator otherIt = componentManager->transformComponents.find(otherEntityID);

            if (shouldCollide(*collisionComponent, *otherCollision))
            {
                if (newPos.collidesWith(otherCollision->boundingBox, Axis::X))
                {
                    sides::Side collisionSide = newPos.getCollisionSide(otherCollision->boundingBox);
                    //For now we are just going to set the velocity to 0 for all entities
                    //We might want to make the ball bounce off things eventually which will have different physics

                    velocityComponent->dx = 0;
                }

            }

        }
        newPos.x = transformComponent->x + (velocityComponent->dx * deltaTime);

        for (std::unordered_map<unsigned int, CollisionComponent*>::iterator otherIter = componentManager->collisionComponents.begin();
            otherIter != componentManager->collisionComponents.end(); otherIter++)
        {
            int otherEntityID = otherIter->first;
            CollisionComponent* otherCollision = otherIter->second;
            std::unordered_map<unsigned int, TransformComponent*>::iterator otherIt = componentManager->transformComponents.find(otherEntityID);

            if (shouldCollide(*collisionComponent, *otherCollision))
            {
                if (newPos.collidesWith(otherCollision->boundingBox, Axis::Y))
                {
                    sides::Side collisionSide = newPos.getCollisionSide(otherCollision->boundingBox);
                    velocityComponent->dy = 0;
                    if (collisionSide == sides::BOTTOM)
                    {
                        hasGroundedCollision = true;
                    }
                }

            }

        }
        newPos.y = transformComponent->y + (velocityComponent->dy * deltaTime);

        transformComponent->grounded = hasGroundedCollision;
        velocityComponent = NULL;
        transformComponent = NULL;
        collisionComponent = NULL;
    }
}

bool CollisionSystem::shouldCollide(CollisionComponent& collider, CollisionComponent& other)
{
    if (collider.layer == CollisionLayer::PLAYER)
    {
        return other.layer == CollisionLayer::TILE || other.layer == CollisionLayer::BALL;
    }
    else if (collider.layer == CollisionLayer::BALL)
    {
        return other.layer == CollisionLayer::TILE
        || other.layer == CollisionLayer::PLAYER
        || other.layer == CollisionLayer::PROJECTILE;
    }
    else if (collider.layer == CollisionLayer::PROJECTILE)
    {
        return other.layer == CollisionLayer::BALL;
    }
    return false;
}

