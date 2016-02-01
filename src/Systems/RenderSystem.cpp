#include "Systems/RenderSystem.h"
#include <unordered_map>
#include <math.h>

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

void RenderSystem::update(float deltaTime)
{
    for (std::unordered_map<unsigned int, RenderComponent*>::iterator iter = componentManager->renderComponents.begin();
        iter != componentManager->renderComponents.end(); iter++)
    {
        int entityID = iter->first;
        RenderComponent* renderComponent = iter->second;

        if (renderComponent->isAnimated)
        {
            //Get the StateComponent, get the current state, update the frame, frame time, frame index etc. and the sourceRect
        }

        std::unordered_map<unsigned int, TransformComponent*>::iterator it = componentManager->transformComponents.find(entityID);
        if ( it != componentManager->transformComponents.end() )
        {
            TransformComponent* transformComponent = it->second;
            SDL_Rect destinationRect = {
                static_cast<int>(ceil(transformComponent->x)),
                static_cast<int>(ceil(transformComponent->y)),
                static_cast<int>(ceil(renderComponent->sourceRect.w)),
                static_cast<int>(ceil(renderComponent->sourceRect.h))
            };
            graphics->blitSurface(renderComponent->spriteSheet, &renderComponent->sourceRect, &destinationRect);
        }
    }

    return;
}
