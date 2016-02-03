#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace globals
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 960;
    const int MAX_OBJECTS = 65000;
    const float GRAVITY = 1000.0f;
    const std::string GAME_NAME = "Wizardball";
}

namespace sides
{
    enum Side
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    inline Side getOppositeSide(Side side)
    {
        return
            side == TOP ? BOTTOM :
            side == BOTTOM ? TOP :
            side == LEFT ? RIGHT :
            side == RIGHT ? LEFT :
            NONE;
    }
}

namespace CollisionLayer
{
    enum Layer
    {
        TILE,
        PLAYER,
        PROJECTILE,
        NONE
    };

}

namespace Direction {
    enum Facing
    {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
}

#endif
