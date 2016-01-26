#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "ComponentManager.h"
#include "InputHandler.h"

class PlayerControlSystem
{
    public:
        PlayerControlSystem();
        PlayerControlSystem(ComponentManager* componentManager, InputHandler* inputHandler);
        ~PlayerControlSystem();
        void update(float deltaTime);
        ComponentManager* componentManager;
        InputHandler* inputHandler;
    protected:
    private:
};

#endif // PLAYERCONTROLSYSTEM_H
