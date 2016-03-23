#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

#include <System.h>
#include "Constants.h"
#include <vector>

struct TransformComponent
{
    inline TransformComponent( int eid, float x, float y, bool grounded = false, Direction::Facing facing = Direction::Facing::NONE) :
        eid(eid),
        x(x),
        y(y),
        grounded(grounded),
        facing(facing)
    {}
     int eid;
    float x;
    float y;
    bool grounded;
    Direction::Facing facing;
};

class TransformSystem : public System
{
    public:
        TransformSystem();
        virtual ~TransformSystem();
        void update(float deltaTime);

        TransformComponent& addComponent( int eid, float x, float y, bool grounded = false );
        bool deleteComponent( int eid);
        bool hasComponent( int eid);
        TransformComponent& getComponent( int eid);

        std::vector<TransformComponent> components;
        std::vector<int> handles;

    protected:
    private:
};

#endif // TRANSFORMSYSTEM_H
