#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <SDL.h>

class PlayerInputComponent
{
public:
    inline PlayerInputComponent(SDL_Scancode jump, SDL_Scancode left, SDL_Scancode right, SDL_Scancode fireballCommand) :
        jumpCommand(jump),
        leftCommand(left),
        rightCommand(right),
        fireballCommand(fireballCommand)
    {};
    SDL_Scancode jumpCommand;
    SDL_Scancode leftCommand;
    SDL_Scancode rightCommand;
    SDL_Scancode fireballCommand;
};

#endif // PLAYERINPUTCOMPONENT_H
