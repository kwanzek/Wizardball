#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Constants.h"

#include <iostream>
class TransformComponent
{
public:
    inline TransformComponent(float x, float y, bool grounded = false, Direction::Facing facing = Direction::Facing::NONE) :
        x(x),
        y(y),
        grounded(grounded),
        facing(facing)
    {}
    float x;
    float y;
    bool grounded;
    Direction::Facing facing;
};

#endif // TRANSFORMCOMPONENT_H
