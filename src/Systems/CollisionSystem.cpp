#include "CollisionSystem.h"

#include <unordered_map>
#include <cmath>
#include <assert.h>
#include <iostream>

CollisionSystem::CollisionSystem():
    System()
{
    components.reserve(100);
    handles.reserve(100);
}

CollisionSystem::CollisionSystem(TransformSystem* transformSystem, MovementSystem* movementSystem) :
    System(),
    transformSystem(transformSystem),
    movementSystem(movementSystem)
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles[i] = -1;
    }
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}

void CollisionSystem::update(float deltaTime)
{
    /*for (std::unordered_map< int, CollisionComponent*>::iterator iter = componentManager->collisionComponents.begin();
        iter != componentManager->collisionComponents.end(); iter++)
    {
       unsigned int entityID = iter->first;
        CollisionComponent* collisionComponent = iter->second;

        //Need to get the velocity and transform components
        TransformComponent* transformComponent = NULL;
        bool hasGroundedCollision = false;
        std::unordered_map< int, TransformComponent*>::iterator it = componentManager->transformComponents.find(entityID);
        if (it != componentManager->transformComponents.end())
        {
            transformComponent = it->second;
        }
        else
        {
            continue;
        }

        VelocityComponent* velocityComponent = NULL;
        std::unordered_map< int, VelocityComponent*>::iterator velocityIt = componentManager->velocityComponents.find(entityID);
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

        for (std::unordered_map< int, CollisionComponent*>::iterator otherIter = componentManager->collisionComponents.begin();
            otherIter != componentManager->collisionComponents.end(); otherIter++)
        {
           unsigned int otherEntityID = otherIter->first;
            if (entityID == otherEntityID)
            {
                continue;
            }
            CollisionComponent* otherCollision = otherIter->second;
            std::unordered_map< int, TransformComponent*>::iterator otherIt = componentManager->transformComponents.find(otherEntityID);

            if (shouldCollide(*collisionComponent, *otherCollision))
            {
                if (newPos.collidesWith(otherCollision->boundingBox, Axis::X))
                {
                    sides::Side collisionSide = newPos.getCollisionSide(otherCollision->boundingBox);
                    //For now we are just going to set the velocity to 0 for all entities
                    //We might want to make the ball bounce off things eventually which will have different physics
                    if (collisionSide == sides::LEFT || collisionSide == sides::RIGHT)
                    {
                        if (collisionComponent->layer == CollisionLayer::PROJECTILE && otherCollision->layer == CollisionLayer::BALL)
                        {
                            VelocityComponent* otherVelocity = NULL;
                            std::unordered_map< int, VelocityComponent*>::iterator otherVelocityIt = componentManager->velocityComponents.find(otherEntityID);
                            if (otherVelocityIt != componentManager->velocityComponents.end())
                            {
                                otherVelocity = otherVelocityIt->second;
                            }

                            Vector2 difference = {
                                static_cast<float>(otherCollision->boundingBox.getCenterX() - collisionComponent->boundingBox.getCenterX()),
                                static_cast<float>(otherCollision->boundingBox.getCenterY() - collisionComponent->boundingBox.getCenterY())
                            };

                            Vector2 unitVector = difference.computeUnitVector();
                            float speed = 200;
                            float xSpeed = unitVector.x * speed;
                            float ySpeed = unitVector.y * speed;
                            otherVelocity->dx = xSpeed;
                            otherVelocity->dy = ySpeed;
                        }
                        else
                        {
                            if (std::abs(newPos.y - otherCollision->boundingBox.getTop()) < collisionComponent->boundingBox.getHeight()-1)
                            {
                                velocityComponent->dx = 0;
                            }
                        }
                    }
                }
            }
        }
        newPos.x = transformComponent->x + (velocityComponent->dx * deltaTime);

        for (std::unordered_map< int, CollisionComponent*>::iterator otherIter = componentManager->collisionComponents.begin();
            otherIter != componentManager->collisionComponents.end(); otherIter++)
        {
           unsigned int otherEntityID = otherIter->first;
            CollisionComponent* otherCollision = otherIter->second;
            std::unordered_map< int, TransformComponent*>::iterator otherIt = componentManager->transformComponents.find(otherEntityID);

            if (shouldCollide(*collisionComponent, *otherCollision))
            {
                if (newPos.collidesWith(otherCollision->boundingBox, Axis::Y))
                {
                    sides::Side collisionSide = newPos.getCollisionSide(otherCollision->boundingBox);
                    if (collisionSide == sides::TOP || collisionSide == sides::BOTTOM)
                    {
                        if (std::abs(newPos.x - otherCollision->boundingBox.getLeft()) < collisionComponent->boundingBox.getWidth()-1)
                        {
                            velocityComponent->dy = 0;
                            if (collisionSide == sides::BOTTOM)
                            {
                                hasGroundedCollision = true;
                            }
                        }

                    }
                }

            }

        }
        newPos.y = transformComponent->y + (velocityComponent->dy * deltaTime);

        transformComponent->grounded = hasGroundedCollision;
        velocityComponent = NULL;
        transformComponent = NULL;
        collisionComponent = NULL;
    }*/
}

CollisionComponent& CollisionSystem::addComponent(
    int eid,
    float x,
    float y,
    float width,
    float height,
    CollisionLayer::Layer layer
)
{
    components.push_back(CollisionComponent(eid, x, y, width, height, layer));
    handles[eid] = components.size()-1;
    return components[components.size()-1];
}

bool CollisionSystem::deleteComponent(int eid)
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

bool CollisionSystem::hasComponent(int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

CollisionComponent& CollisionSystem::getComponent(int eid)
{
    assert (eid < handles.capacity() && this->hasComponent(eid));
    return components[handles[eid]];
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

