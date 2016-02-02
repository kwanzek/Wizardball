#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Utils/Rectangle.h"
#include "Constants.h"

class CollisionComponent
{
public:

    inline CollisionComponent(float x, float y, float width, float height, CollisionLayer::Layer layer)
    {
        this->layer = layer;
        boundingBox = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };
    };

    CollisionLayer::Layer layer;
    Rectangle boundingBox;
};

#endif // COLLISIONCOMPONENT_H
