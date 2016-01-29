#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "Components/RenderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PlayerInputComponent.h"
#include "Components/PlayerControllerComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/CollisionComponent.h"

#include "Graphics.h"

#include <unordered_map>
#include <iostream>
#include <string>

class ComponentManager
{
    public:
        ComponentManager();
        ComponentManager(Graphics* graphics);
        ~ComponentManager();
        std::unordered_map<unsigned int, RenderComponent *> renderComponents;
        std::unordered_map<unsigned int, TransformComponent *> transformComponents;
        std::unordered_map<unsigned int, PlayerInputComponent *> playerInputComponents;
        std::unordered_map<unsigned int, PlayerControllerComponent *> playerControllerComponents;
        std::unordered_map<unsigned int, VelocityComponent *> velocityComponents;
        std::unordered_map<unsigned int, CollisionComponent *> collisionComponents;

        TransformComponent* makeTransformComponent(unsigned int eid, float x, float y);
        RenderComponent* makeRenderComponent(unsigned int eid, int x, int y, int width, int height, std::string texturePath);
        PlayerInputComponent* makePlayerInputComponent(unsigned int eid, SDL_Scancode jump, SDL_Scancode left, SDL_Scancode right);
        PlayerControllerComponent* makePlayerControllerComponent(unsigned int eid);
        VelocityComponent* makeVelocityComponent(unsigned int eid, float dx, float dy, float maxXSpeedGround, float maxXSpeedAir, float maxYSpeed);
        CollisionComponent* makeCollisionComponent(unsigned int eid, float x, float y, float width, float height, CollisionLayer layer);

        Graphics* graphics;

    protected:
    private:
};

#endif // COMPONENTMANAGER_H
