#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

//Convenience struct for holding pairs of numbers
struct Vector2
{
    float x,y;
    Vector2() :
        x(0), y(0) {}
    Vector2(float x, float y) :
        x(x), y(y) {}
    inline float magnitude()
    {
        if (x == 0 && y == 0)
        {
            return 0;
        }
        else
        {
            float inner = std::pow(x,2) + std::pow(y,2);
            return std::sqrt(inner);
        }
    }
    Vector2 computeUnitVector()
    {
        float magnitudeVal = this->magnitude();
        if (magnitudeVal == 0)
        {
            return Vector2();
        }
        else
        {
            Vector2 uv = Vector2(x/magnitudeVal, y/magnitudeVal);
            return uv;
        }
    }
};

#endif // VECTOR2_H
