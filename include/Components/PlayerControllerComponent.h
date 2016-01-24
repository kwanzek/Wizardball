#ifndef PLAYERCONTROLLERCOMPONENT_H
#define PLAYERCONTROLLERCOMPONENT_H

class PlayerControllerComponent
{
public:
    inline PlayerControllerComponent(){};
    enum PlayerState {
        IDLE,
        RUNNING,
        JUMPING
    };
    PlayerState state;
};

#endif // PLAYERCONTROLLERCOMPONENT_H
