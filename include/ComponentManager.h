#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "Components/RenderComponent.h"
#include "Components/TransformComponent.h"
#include "Graphics.h"

#include <map>
#include <iostream>
#include <string>

class ComponentManager
{
    public:
        ComponentManager();
        ComponentManager(Graphics* graphics);
        ~ComponentManager();
        std::map<unsigned int, RenderComponent *> renderComponents;
        std::map<unsigned int, TransformComponent *> transformComponents;

        TransformComponent* makeTransformComponent(unsigned int eid, float x, float y);
        RenderComponent* makeRenderComponent(unsigned int eid, int x, int y, int width, int height, std::string texturePath);

        Graphics* graphics;
    protected:
    private:
};

#endif // COMPONENTMANAGER_H
