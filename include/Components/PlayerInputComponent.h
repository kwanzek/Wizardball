#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <SDL.h>

enum PlayerCommand
{
    JUMP,
    LEFT,
    RIGHT,
    FIREBALL
};

class PlayerInputComponent
{
public:

    inline PlayerInputComponent (
        SDL_Scancode jump,
        SDL_Scancode left,
        SDL_Scancode right,
        SDL_Scancode fireballCommand,
        SDL_JoystickID joystickID = -1,
        int joyJumpButton = -1,
        int joyFireballButton = -1

    ) :
        jumpCommand(jump),
        leftCommand(left),
        rightCommand(right),
        fireballCommand(fireballCommand),
        joystickID(joystickID),
        joyJumpButton(joyJumpButton),
        joyFireballButton(joyFireballButton)
    {};
    SDL_Scancode jumpCommand;
    SDL_Scancode leftCommand;
    SDL_Scancode rightCommand;
    SDL_Scancode fireballCommand;
    SDL_JoystickID joystickID;
    int joyJumpButton;
    int joyFireballButton;
};

#endif // PLAYERINPUTCOMPONENT_H
