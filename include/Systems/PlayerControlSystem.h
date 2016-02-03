#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "ComponentManager.h"
#include "InputHandler.h"
#include "EntityFactory.h"
#include "Constants.h"

class PlayerControlSystem
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
