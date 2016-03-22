#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "InputHandler.h"
#include "Constants.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/StateSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "EntityFactory.h"
#include "System.h"

class EntityFactory;

class PlayerControllerComponent
{
public:
    inline PlayerControllerComponent(int eid):
        eid(eid)
    {};
    int eid;
    enum PlayerState {
        IDLE,
        RUNNING,
        JUMPING
    };
    PlayerState state;
    float jumpForce = 150.f;
};

class PlayerControlSystem : public System
{
    public:
        PlayerControlSystem();
        PlayerControlSystem(
            InputHandler* inputHandler,
            TransformSystem* ts,
            MovementSystem* ms,
            StateSystem* ss,
            PlayerInputSystem* pis
        );
        ~PlayerControlSystem();
        void update(float deltaTime);

        PlayerControllerComponent& addComponent(int eid);
        bool deleteComponent(int eid);
        bool hasComponent(int eid);
        PlayerControllerComponent& getComponent(int eid);

        InputHandler* inputHandler;
        TransformSystem* transformSystem;
        MovementSystem* movementSystem;
        StateSystem* stateSystem;
        PlayerInputSystem* playerInputSystem;
        //TODO: This should be behind a service locator
        EntityFactory* entityFactory;

        std::vector<PlayerControllerComponent> components;
        std::vector<int> handles;

        bool didAction(PlayerCommand playerCommand, PlayerInputComponent& playerInputComponent);
    protected:
    private:
};

#endif // PLAYERCONTROLSYSTEM_H
