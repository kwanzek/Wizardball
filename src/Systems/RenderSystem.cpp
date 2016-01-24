#include "Systems/RenderSystem.h"

RenderSystem::RenderSystem()
{
    //ctor
}

RenderSystem::RenderSystem(ComponentManager* componentManager, Graphics* graphics)
{
    this->componentManager = componentManager;
    this->graphics = graphics;
}

RenderSystem::~RenderSystem()
{
    //dtor
}

void RenderSystem::update(float elapsedTime)
{
    for (std::map<unsigned int, RenderComponent*>::iterator iter = componentManager->renderComponents.begin();
        iter != componentManager->renderComponents.end(); iter++)
    {
        int entityID = iter->first;
        RenderComponent* renderComponent = iter->second;

        std::map<unsigned int, TransformComponent*>::iterator it = componentManager->transformComponents.find(entityID);
        if ( it != componentManager->transformComponents.end() )
        {
            TransformComponent* transformComponent = it->second;
            SDL_Rect destinationRect = {
                static_cast<int>(transformComponent->x),
                static_cast<int>(transformComponent->y),
                static_cast<int>(renderComponent->sourceRect.w),
                static_cast<int>(renderComponent->sourceRect.h)
            };
            graphics->blitSurface(renderComponent->spriteSheet, &renderComponent->sourceRect, &destinationRect);
        }
    }

    return;
}
