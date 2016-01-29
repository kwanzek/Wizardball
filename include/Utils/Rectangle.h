#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Constants.h"

#include <iostream>
#include <cmath>

class Rectangle
{
public:
    Rectangle() {};
    Rectangle(int x, int y, int width, int height) :
        x(x),
        y(y),
        width(width),
        height(height)
    {

    }

    int x;
    int y;
    int width;
    int height;

    const int getCenterX() const { return this->x + this->width / 2; }
    const int getCenterY() const { return this->y + this->height / 2; }

    const int getLeft() const { return this->x; }
    const int getRight() const { return this->x + this->width; }
    const int getTop() const { return this->y; }
    const int getBottom() const { return this->y + this->height; }

    const int getWidth() const { return this->width; }
    const int getHeight() const { return this->height; }

    const int getSide(const sides::Side side) const
    {
        return
            side == sides::LEFT ? this->getLeft() :
            side == sides::RIGHT ? this->getRight() :
            side == sides::TOP ? this->getTop() :
            side == sides::BOTTOM ? this->getBottom() :
            sides::NONE;
    }

    //Takes in another Rectangle and checks if the two are colliding
    const bool collidesWith(const Rectangle &other) const
    {
        return
            this->getRight() >= other.getLeft() &&
            this->getLeft() <= other.getRight() &&
            this->getTop() <= other.getBottom() &&
            this->getBottom() >= other.getTop();
    }

    sides::Side getCollisionSide(const Rectangle &other)
    {
      //How far the collision is on each side, the lowest amount is the side we are overlaping on
        int amtRight;
        int amtLeft;
        int amtTop;
        int amtBottom;

        amtRight = std::abs(this->getRight() - other.getLeft());
        amtLeft = std::abs(this->getLeft() - other.getRight());
        amtTop = std::abs(this->getTop() - other.getBottom());
        amtBottom = std::abs(this->getBottom() - other.getTop());

        if (amtRight <= amtLeft && amtRight <= amtTop && amtRight <= amtBottom)
        {
            return sides::RIGHT;
        }
        else if (amtLeft <= amtRight && amtLeft <= amtTop && amtLeft <= amtBottom)
        {
            return sides::LEFT;
        }
        else if (amtBottom <= amtRight && amtBottom <= amtTop && amtBottom <= amtLeft)
        {
            return sides::BOTTOM;
        }
        else if (amtTop <= amtRight && amtTop <= amtBottom && amtTop <= amtLeft)
        {
            return sides::TOP;
        }

        return sides::NONE;
    }

    const bool isValidRectangle() const
    {
        return (this->x >= 0 && this->y >= 0 && this->width >= 0 && this->height >= 0);
    }

private:


};

#endif // RECTANGLE_H
