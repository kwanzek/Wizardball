#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <iostream>
class TransformComponent
{
public:
    inline TransformComponent(float x, float y) :
        x(x),
        y(y)
    {}
    float x;
    float y;
};

#endif // TRANSFORMCOMPONENT_H
