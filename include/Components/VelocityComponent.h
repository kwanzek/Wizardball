#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <iostream>
class VelocityComponent
{
public:
    inline VelocityComponent(float dx, float dy, float maxXSpeedGround, float maxXSpeedAir, float maxYSpeed) :
        dx(dx),
        dy(dy),
        maxXSpeedGround(maxXSpeedGround),
        maxXSpeedAir(maxXSpeedAir),
        maxYSpeed(maxYSpeed)
    {}
    float dx;
    float dy;
    float maxXSpeedGround;
    float maxXSpeedAir;
    float maxYSpeed;
};

#endif // VELOCITYCOMPONENT_H
