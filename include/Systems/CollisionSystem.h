#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iterator>
#include <vector>

#include "MovementSystem.h"
#include "TransformSystem.h"
#include "PlayerControlSystem.h"
#include "Constants.h"
#include "System.h"

#include "Utils/Rectangle.h"

class PlayerControlSystem;

struct CollisionComponent
{
public:

    inline CollisionComponent(int eid, float x, float y, float width, float height, CollisionLayer::Layer layer, bool enabled = true)
    {
        this->layer = layer;
        this->eid = eid;
        boundingBox = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };
        this->enabled = enabled;
    };

    int eid;
    CollisionLayer::Layer layer;
    Rectangle boundingBox;
    bool enabled;
    bool ignoreOneFrame = false;
};

class CollisionSystem : public System
{
    public:
        CollisionSystem();
        CollisionSystem(TransformSystem* transformSystem, MovementSystem* movementSystem, PlayerControlSystem* PCS);
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
        PlayerControlSystem* playerControlSystem;

        std::vector<CollisionComponent> components;
        std::vector<int> handles;

        bool shouldCollide(CollisionComponent& collider, CollisionComponent& other);
        void handleCollision(
            Rectangle& newPos,
            TransformComponent& transformComponent,
            CollisionComponent& collisionComponent,
            VelocityComponent& velocityComponent,
            CollisionComponent& otherCollision,
            Axis::Axis axis,
            float deltaTime
        );
    protected:
    private:
};

#endif // COLLISIONSYSTEM_H
