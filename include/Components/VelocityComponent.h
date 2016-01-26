#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <iostream>
class VelocityComponent
{
public:
    inline VelocityComponent(float dx, float dy) :
        dx(dx),
        dy(dy)
    {}
    float dx;
    float dy;
};

#endif // VELOCITYCOMPONENT_H
