#ifndef PICKUPSYSTEM_H
#define PICKUPSYSTEM_H

#include <vector>
#include "System.h"
#include "Systems/TransformSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/MovementSystem.h"

struct PickupComponent
{
public:

    inline PickupComponent(int eid, int otherEID)
    {
        this->eid = eid;
        this->otherEID = otherEID;
    };

   int eid;
   int otherEID;
};

class CollisionSystem;
class PickupSystem : public System
{
    public:
        PickupSystem();
        PickupSystem(TransformSystem* transformSystem, MovementSystem* movementSystem);
        virtual ~PickupSystem();
        void update(float deltaTime);

        PickupComponent& addComponent(int eid, int otherEID);
        bool deleteComponent(int eid);
        bool hasComponent(int eid);
        PickupComponent& getComponent(int eid);

        void throwBall(int eid, int otherEID);
        void pickupBall(int eid, int otherEID);

        TransformSystem* transformSystem;
        CollisionSystem* collisionSystem;
        MovementSystem* movementSystem;
        std::vector<int> handles;
        std::vector<PickupComponent> components;
    protected:
    private:
};

#endif // PICKUPSYSTEM_H
