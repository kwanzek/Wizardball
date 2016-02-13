#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "Utils/Vector2.h"
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
    float baseIgnoreGravityTime = .3f;
    float currentIgnoreGravityTime = 0;
    bool ignoreGravity = false;
};

#endif // VELOCITYCOMPONENT_H
