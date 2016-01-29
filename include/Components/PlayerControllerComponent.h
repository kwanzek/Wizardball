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
    float jumpForce = 0.005f;
};

#endif // PLAYERCONTROLLERCOMPONENT_H
