#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iterator>
#include <vector>

#include "MovementSystem.h"
#include "TransformSystem.h"
#include "Constants.h"
#include "System.h"

#include "Utils/Rectangle.h"

struct CollisionComponent
{
public:

    inline CollisionComponent(int eid, float x, float y, float width, float height, CollisionLayer::Layer layer)
    {
        this->layer = layer;
        this->eid = eid;
        boundingBox = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };
    };

    int eid;
    CollisionLayer::Layer layer;
    Rectangle boundingBox;
};

class CollisionSystem : public System
{
    public:
        CollisionSystem();
        CollisionSystem(TransformSystem* transformSystem, MovementSystem* movementSystem);
        ~CollisionSystem();
        void update(float deltaTime);

        CollisionComponent& addComponent(
            int eid,
            float x,
            float y,
            float width,
            float height,
            CollisionLayer::Layer layer
        );
        bool deleteComponent(int eid);
        bool hasComponent(int eid);
        CollisionComponent& getComponent(int eid);

        TransformSystem* transformSystem;
        MovementSystem* movementSystem;

        std::vector<CollisionComponent> components;
        std::vector<int> handles;

        bool shouldCollide(CollisionComponent& collider, CollisionComponent& other);
    protected:
    private:
};

#endif // COLLISIONSYSTEM_H
