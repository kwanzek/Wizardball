#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ComponentManager.h"

#include <iterator>
#include "System.h"

class MovementSystem : public System
{
    public:
        MovementSystem();
        MovementSystem(ComponentManager* componentManager);
        ~MovementSystem();
        void update(float deltaTime);
        ComponentManager* componentManager;
    protected:
    private:
};

#endif // MOVEMENTSYSTEM_H
