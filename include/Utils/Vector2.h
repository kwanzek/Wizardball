#ifndef VECTOR2_H
#define VECTOR2_H

//Convenience struct for holding pairs of numbers
struct Vector2
{
    int x,y;
    Vector2() :
        x(0), y(0) {}
    Vector2(int x, int y) :
        x(x), y(y) {}
};

#endif // VECTOR2_H
