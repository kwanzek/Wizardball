#include "ComponentManager.h"
#include <iostream>

ComponentManager::ComponentManager()
{
    //ctor
}

ComponentManager::ComponentManager(Graphics* graphics) :
    graphics(graphics) {}

ComponentManager::~ComponentManager()
{
    //dtor
}

TransformComponent* ComponentManager::makeTransformComponent(unsigned int eid, float x, float y)
{
    TransformComponent* component = new TransformComponent(x,y);
    transformComponents.insert(std::make_pair(eid, component));
    return component;
}

RenderComponent* ComponentManager::makeRenderComponent(unsigned int eid, int x, int y, int width, int height, std::string texturePath)
{
    SDL_Rect sourceRect = { x, y, width, height };
    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(graphics->getRenderer(), graphics->loadImage(texturePath));
    RenderComponent* component = new RenderComponent(sourceRect, spriteSheet);
    renderComponents.insert(std::make_pair(eid, component));
    return component;
}
