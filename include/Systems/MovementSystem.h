#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <iterator>
#include "System.h"
#include "Utils/Vector2.h"
#include "Systems/TransformSystem.h"

struct VelocityComponent
{
    inline VelocityComponent(
        int eid,
        float dx,
        float dy,
        float maxXSpeedGround,
        float maxXSpeedAir,
        float maxYSpeed,
        float xFriction,
        float baseIgnoreGravityTime,
        float currentIgnoreGravityTime,
        bool ignoreGravity,
        bool enabled = true
    ) :
        eid(eid),
        dx(dx),
        dy(dy),
        maxXSpeedGround(maxXSpeedGround),
        maxXSpeedAir(maxXSpeedAir),
        maxYSpeed(maxYSpeed),
        xFriction(xFriction),
        baseIgnoreGravityTime(baseIgnoreGravityTime),
        currentIgnoreGravityTime(currentIgnoreGravityTime),
        ignoreGravity(ignoreGravity),
        enabled(enabled)
    {}
    int eid;
    float dx;
    float dy;
    float maxXSpeedGround;
    float maxXSpeedAir;
    float maxYSpeed;
    float xFriction;
    float baseIgnoreGravityTime;
    float currentIgnoreGravityTime;
    bool ignoreGravity;
    bool enabled;
};

class MovementSystem : public System
{
    public:
        MovementSystem();
        MovementSystem(TransformSystem* transformSystem);
        ~MovementSystem();
        void update(float deltaTime);

        VelocityComponent& addComponent(
            int eid,
            float dx,
            float dy,
            float maxXSpeedGround,
            float maxXSpeedAir,
            float maxYSpeed,
            float xFriction = 0.0f,
            float baseIgnoreGravityTime = 0.3f,
            float currentIgnoreGravityTime = 0.0f,
            bool ignoreGravity = false
        );
        bool deleteComponent(int eid);
        bool hasComponent(int eid);
        VelocityComponent& getComponent(int eid);

        TransformSystem* transformSystem;
        std::vector<VelocityComponent> components;
        std::vector<int> handles;

    protected:
    private:
};

#endif // MOVEMENTSYSTEM_H
