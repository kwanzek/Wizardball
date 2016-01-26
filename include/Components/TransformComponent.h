#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <iostream>
class TransformComponent
{
public:
    inline TransformComponent(float x, float y, bool grounded = false) :
        x(x),
        y(y),
        grounded(grounded)
    {}
    float x;
    float y;
    bool grounded;
};

#endif // TRANSFORMCOMPONENT_H
