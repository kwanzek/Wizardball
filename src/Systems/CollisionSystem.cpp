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

CollisionSystem::CollisionSystem(TransformSystem* transformSystem, MovementSystem* movementSystem, PlayerControlSystem* PCS) :
    System(),
    transformSystem(transformSystem),
    movementSystem(movementSystem),
    playerControlSystem(PCS)
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
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
        if (!collisionComponent.enabled)
        {
            continue;
        }
        int eid = collisionComponent.eid;
        if (transformSystem->hasComponent(eid) && movementSystem->hasComponent(eid))
        {
            bool hasGroundedCollision = false;
            TransformComponent& transformComponent = transformSystem->getComponent(eid);
            collisionComponent.boundingBox.x = static_cast<int>(transformComponent.x);
            collisionComponent.boundingBox.y = static_cast<int>(transformComponent.y);

            VelocityComponent& velocityComponent = movementSystem->getComponent(eid);
            Rectangle newPos = Rectangle(
                collisionComponent.boundingBox.getLeft() + velocityComponent.dx * deltaTime,
                collisionComponent.boundingBox.getTop() + velocityComponent.dy * deltaTime,
                collisionComponent.boundingBox.getWidth(),
                collisionComponent.boundingBox.getHeight()
            );

            Direction::Facing forwardDirX = velocityComponent.dx < 0 ? Direction::LEFT : Direction::RIGHT;
            Direction::Facing forwardDirY = velocityComponent.dy < 0 ? Direction::UP : Direction::DOWN;

            int forwardEdgeX = forwardDirX == Direction::LEFT ? collisionComponent.boundingBox.getLeft() : collisionComponent.boundingBox.getRight();
            int forwardEdgeY = forwardDirY == Direction::UP ? collisionComponent.boundingBox.getTop() : collisionComponent.boundingBox.getBottom();

            int wantToMoveToX = forwardDirX == Direction::LEFT ? newPos.getLeft() : newPos.getRight();
            int wantToMoveToY = forwardDirY == Direction::UP ? newPos.getTop() : newPos.getBottom();

            int canMoveDistanceX = wantToMoveToX - forwardEdgeX;
            int canMoveDistanceY = wantToMoveToY - forwardEdgeY;

            bool hasCollision = false;

            for (unsigned int j = 0; j < components.size(); ++j)
            {
                if (j != i)
                {
                    CollisionComponent& otherCollision = components[j];
                    if (otherCollision.enabled && shouldCollide(collisionComponent, otherCollision) && newPos.collidesWith(otherCollision.boundingBox))
                    {
                        int otherEdgeX = forwardDirX == Direction::LEFT ? otherCollision.boundingBox.getRight() : otherCollision.boundingBox.getLeft();
                        int otherEdgeY = forwardDirY == Direction::UP ? otherCollision.boundingBox.getBottom() : otherCollision.boundingBox.getTop();
                        if (otherEdgeY != forwardEdgeY && abs(otherEdgeX-forwardEdgeX) <= abs(canMoveDistanceX))
                        {
                            hasCollision = true;
                            canMoveDistanceX = otherEdgeX-forwardEdgeX;
                            if (collisionComponent.layer == CollisionLayer::PLAYER && otherCollision.layer == CollisionLayer::BALL)
                            {
                                playerControlSystem->handleBallCollision(eid, otherCollision.eid);
                            }
                        }
                        //this->handleCollision(newPos, transformComponent, collisionComponent, velocityComponent, otherCollision, axis, deltaTime);
                    }
                }
            }
            if (hasCollision)
            {
                velocityComponent.dx = canMoveDistanceX/deltaTime;
                transformComponent.x = collisionComponent.boundingBox.x;
            }
            collisionComponent.boundingBox.x = transformComponent.x + velocityComponent.dx * deltaTime;
            forwardEdgeX = forwardDirX == Direction::LEFT ? collisionComponent.boundingBox.getLeft() : collisionComponent.boundingBox.getRight();
            hasCollision = false;

            for (unsigned int j = 0; j < components.size(); ++j)
            {
                CollisionComponent& otherCollision = components[j];
                if (j != i)
                {
                    if (otherCollision.enabled && shouldCollide(collisionComponent, otherCollision) && newPos.collidesWith(otherCollision.boundingBox))
                    {
                        int otherEdgeX = forwardDirX == Direction::LEFT ? otherCollision.boundingBox.getRight() : otherCollision.boundingBox.getLeft();
                        int otherEdgeY = forwardDirY == Direction::UP ? otherCollision.boundingBox.getBottom() : otherCollision.boundingBox.getTop();
                        if (otherEdgeX != forwardEdgeX && abs(otherEdgeY-forwardEdgeY) <= abs(canMoveDistanceY))
                        {
                            hasCollision = true;
                            if (forwardDirY == Direction::DOWN)
                            {
                                hasGroundedCollision = true;
                            }
                            if (collisionComponent.layer == CollisionLayer::PLAYER && otherCollision.layer == CollisionLayer::BALL)
                            {
                                playerControlSystem->handleBallCollision(eid, otherCollision.eid);
                            }
                            canMoveDistanceY = otherEdgeY-forwardEdgeY;
                        }
                        //this->handleCollision(newPos, transformComponent, collisionComponent, velocityComponent, otherCollision, axis, deltaTime);

                    }
                }
            }

            if (hasCollision)
            {
                velocityComponent.currentIgnoreGravityTime = 0.0f;
                //velocityComponent.dy = canMoveDistanceY/deltaTime;
                velocityComponent.dy = 0;
                transformComponent.y = collisionComponent.boundingBox.y;
            }

            transformComponent.grounded = hasGroundedCollision;
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
        edgeVal = forwardDir == Direction::LEFT ? collisionComponent.boundingBox.getLeft() : collisionComponent.boundingBox.getRight();
        otherEdgeVal = forwardDir == Direction::RIGHT ? otherCollision.boundingBox.getRight() : otherCollision.boundingBox.getLeft();
        if (forwardDir == Direction::LEFT && edgeVal <= otherEdgeVal)
            return;
        if (forwardDir == Direction::RIGHT && edgeVal >= otherEdgeVal)
            return;
        curVelocity = velocityComponent.dx;
    }
    else
    {
        forwardDir = velocityComponent.dy < 0 ? Direction::UP : Direction::DOWN;
        edgeVal = forwardDir == Direction::UP ? collisionComponent.boundingBox.getTop() : collisionComponent.boundingBox.getBottom();
        otherEdgeVal = forwardDir == Direction::UP ? otherCollision.boundingBox.getBottom() : otherCollision.boundingBox.getTop();
        curVelocity = velocityComponent.dy;
    }
    int diff = otherEdgeVal - edgeVal;
    float newVelocity = diff/deltaTime;
    newVelocity = std::min(abs(newVelocity), abs(curVelocity));
    newVelocity = 0;
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

