#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <SDL.h>

class PlayerInputComponent
{
public:
    inline PlayerInputComponent(SDL_Scancode jump, SDL_Scancode left, SDL_Scancode right) :
        jumpCommand(jump),
        leftCommand(left),
        rightCommand(right)
    {};
    SDL_Scancode jumpCommand;
    SDL_Scancode leftCommand;
    SDL_Scancode rightCommand;
};

#endif // PLAYERINPUTCOMPONENT_H
