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
#include "Components/StateComponent.h"
#include "Components/PickupComponent.h"

#include "Graphics.h"

#include "SDL.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

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
        std::unordered_map<unsigned int, StateComponent *> stateComponents;
        std::unordered_map<unsigned int, PickupComponent *> pickupComponents;

        TransformComponent* makeTransformComponent(unsigned int eid, float x, float y);

        PlayerControllerComponent* makePlayerControllerComponent(unsigned int eid);
        VelocityComponent* makeVelocityComponent(
            unsigned int eid,
            float dx,
            float dy,
            float maxXSpeedGround = 0,
            float maxXSpeedAir = 0,
            float maxYSpeed = 0
        );
        CollisionComponent* makeCollisionComponent(unsigned int eid, float x, float y, float width, float height, CollisionLayer::Layer layer);

        RenderComponent* makeRenderComponent(
            unsigned int eid,
            int x,
            int y,
            int width,
            int height,
            std::string texturePath,
            bool animated = false,
            std::unordered_map<std::string, std::vector<SDL_Rect>> animations = std::unordered_map<std::string, std::vector<SDL_Rect>>(),
            std::string currentAnimation = "",
            float timeToUpdate = 1.f
        );

        PickupComponent* makePickupComponent(unsigned int eid, unsigned int othereid);

        Graphics* graphics;

    protected:
    private:
};

#endif // COMPONENTMANAGER_H
