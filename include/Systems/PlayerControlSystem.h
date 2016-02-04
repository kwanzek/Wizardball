#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "ComponentManager.h"
#include "InputHandler.h"
#include "EntityFactory.h"
#include "Constants.h"
#include "System.h"

class PlayerControlSystem : public System
{
    public:
        PlayerControlSystem();
        PlayerControlSystem(ComponentManager* componentManager, EntityFactory* entityFactory, InputHandler* inputHandler);
        ~PlayerControlSystem();
        void update(float deltaTime);
        ComponentManager* componentManager;
        EntityFactory* entityFactory;
        InputHandler* inputHandler;
    protected:
    private:
};

#endif // PLAYERCONTROLSYSTEM_H
