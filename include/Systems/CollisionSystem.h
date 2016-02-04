#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iterator>

#include "ComponentManager.h"
#include "Constants.h"
#include "System.h"

class CollisionSystem : public System
{
    public:
        CollisionSystem();
        CollisionSystem(ComponentManager* componentManager);
        ~CollisionSystem();
        void update(float deltaTime);
        ComponentManager* componentManager;
    protected:
    private:
};

#endif // COLLISIONSYSTEM_H
