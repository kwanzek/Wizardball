#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include <System.h>
#include <SDL.h>
#include <vector>

enum PlayerCommand
{
    JUMP,
    LEFT,
    RIGHT,
    FIREBALL,
    PICKUP
};

struct PlayerInputComponent
{
    inline PlayerInputComponent (
        int eid,
        SDL_Scancode jump,
        SDL_Scancode left,
        SDL_Scancode right,
        SDL_Scancode fireballCommand,
        SDL_Scancode pickupCommand,
        SDL_JoystickID joystickID = -1,
        int joyJumpButton = -1,
        int joyFireballButton = -1,
        int joyPickupButton = -1

    ) :
        eid(eid),
        jumpCommand(jump),
        leftCommand(left),
        rightCommand(right),
        fireballCommand(fireballCommand),
        pickupCommand(pickupCommand),
        joystickID(joystickID),
        joyJumpButton(joyJumpButton),
        joyFireballButton(joyFireballButton),
        joyPickupButton(joyPickupButton)
    {};
    int eid;
    SDL_Scancode jumpCommand;
    SDL_Scancode leftCommand;
    SDL_Scancode rightCommand;
    SDL_Scancode fireballCommand;
    SDL_Scancode pickupCommand;
    SDL_JoystickID joystickID;
    int joyJumpButton;
    int joyFireballButton;
    int joyPickupButton;
};

class PlayerInputSystem : public System
{
    public:
        PlayerInputSystem();
        virtual ~PlayerInputSystem();
        void update(float deltaTime);

        PlayerInputComponent& addComponent(
             int eid,
            SDL_Scancode jump,
            SDL_Scancode left,
            SDL_Scancode right,
            SDL_Scancode fireball,
            SDL_Scancode pickup,
            SDL_JoystickID joystickID = -1,
            int joyButtonJump = -1,
            int joyButtonFireball = -1,
            int joyButtonPickup = -1
        );
        bool deleteComponent(int eid);
        bool hasComponent(int eid);
        PlayerInputComponent& getComponent(int eid);

        std::vector<PlayerInputComponent> components;
        std::vector<int> handles;

    protected:
    private:
};

#endif // PLAYERINPUTSYSTEM_H
