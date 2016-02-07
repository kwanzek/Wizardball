#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <SDL.h>

class PlayerInputComponent
{
public:
    inline PlayerInputComponent(
        SDL_Scancode jump,
        SDL_Scancode left,
        SDL_Scancode right,
        SDL_Scancode fireballCommand,
        SDL_JoystickID joystickID = -1
    ) :
        jumpCommand(jump),
        leftCommand(left),
        rightCommand(right),
        fireballCommand(fireballCommand),
        joystickID(joystickID)
    {};
    SDL_Scancode jumpCommand;
    SDL_Scancode leftCommand;
    SDL_Scancode rightCommand;
    SDL_Scancode fireballCommand;
    SDL_JoystickID joystickID;
};

#endif // PLAYERINPUTCOMPONENT_H
