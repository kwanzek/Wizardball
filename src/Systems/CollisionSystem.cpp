#include "CollisionSystem.h"

#include <unordered_map>
#include <cmath>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

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
    for (unsigned int i = 0; i < components.size(); ++i)
    {
        CollisionComponent& collisionComponent = components[i];
        int eid = collisionComponent.eid;
        if (transformSystem->hasComponent(eid) && movementSystem->hasComponent(eid))
        {
            bool hasGroundedCollision = false;
            TransformComponent& transformComponent = transformSystem->getComponent(eid);
            VelocityComponent& velocityComponent = movementSystem->getComponent(eid);

            Rectangle newPos = Rectangle(
                collisionComponent.boundingBox.getLeft() + velocityComponent.dx * deltaTime,
                collisionComponent.boundingBox.getTop() + velocityComponent.dy * deltaTime,
                collisionComponent.boundingBox.getWidth(),
                collisionComponent.boundingBox.getHeight()
            );

            if (eid == 0)
            {



                std::cout << "ColXY: " << collisionComponent.boundingBox.x << ", " << collisionComponent.boundingBox.y << " ";
                std::cout << "ColLeftTop: " << collisionComponent.boundingBox.getLeft() << ", " << collisionComponent.boundingBox.getTop() << " ";
                std::cout << "NewPosXY: " << newPos.x << "," << newPos.y << " ";
                std::cout << "NewPosLeftOP: " << newPos.getLeft() << ", " << newPos.getTop() << std::endl;
            }
            //Get forward Y
            Axis::Axis axis = Axis::Y;
            Direction::Facing forwardDir = velocityComponent.dy < 0 ? Direction::UP : Direction::DOWN;
            for (unsigned int j = i+1; j < components.size(); ++j)
            {
                CollisionComponent& otherCollision = components[j];
                if (shouldCollide(collisionComponent, otherCollision) && newPos.collidesWith(otherCollision.boundingBox))
                {
                    this->handleCollision(newPos, transformComponent, collisionComponent, velocityComponent, otherCollision, axis, deltaTime);
                    if (forwardDir == Direction::DOWN)
                    {
                        hasGroundedCollision = true;
                    }
                }
            }

            //Get forward X and do it again
            axis = Axis::X;
            for (unsigned int j = i+1; j < components.size(); ++j)
            {
                CollisionComponent& otherCollision = components[j];
                if (shouldCollide(collisionComponent, otherCollision) && newPos.collidesWith(otherCollision.boundingBox))
                {
                    this->handleCollision(newPos, transformComponent, collisionComponent, velocityComponent, otherCollision, axis, deltaTime);
                }
            }
            transformComponent.grounded = hasGroundedCollision;
            collisionComponent.boundingBox.x = newPos.x;
            collisionComponent.boundingBox.y = newPos.y;
        }
    }
}

void CollisionSystem::handleCollision(
    Rectangle& newPos,
    TransformComponent& transformComponent,
    CollisionComponent& collisionComponent,
    VelocityComponent& velocityComponent,
    CollisionComponent& otherCollision,
    Axis::Axis axis,
    float deltaTime
)
{
    assert(deltaTime > 0);
    Direction::Facing forwardDir;
    int edgeVal;
    int otherEdgeVal;
    float curVelocity = 0.0f;
    if (axis == Axis::X)
    {
        forwardDir = velocityComponent.dx < 0 ? Direction::LEFT : Direction::RIGHT;
        edgeVal = forwardDir == Direction::LEFT ? newPos.getLeft() : newPos.getRight();
        otherEdgeVal = forwardDir == Direction::RIGHT ? otherCollision.boundingBox.getRight() : otherCollision.boundingBox.getLeft();
        curVelocity = velocityComponent.dx;
    }
    else
    {
        forwardDir = velocityComponent.dy < 0 ? Direction::UP : Direction::DOWN;
        edgeVal = forwardDir == Direction::UP ? newPos.getTop() : newPos.getBottom();
        otherEdgeVal = forwardDir == Direction::UP ? otherCollision.boundingBox.getBottom() : otherCollision.boundingBox.getTop();
        curVelocity = velocityComponent.dy;
    }
    int diff = otherEdgeVal - edgeVal;
    float newVelocity = diff/deltaTime;
    newVelocity = std::min(abs(newVelocity), abs(curVelocity));
    if (forwardDir == Direction::UP || forwardDir == Direction::LEFT)
    {
        newVelocity *= -1;
    }
    if (axis == Axis::X)
    {
        velocityComponent.dx = newVelocity;
        newPos.x = transformComponent.x + velocityComponent.dx * deltaTime;
    }
    else
    {
        velocityComponent.dy = newVelocity;
        newPos.y = transformComponent.y + velocityComponent.dy * deltaTime;
    }
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

