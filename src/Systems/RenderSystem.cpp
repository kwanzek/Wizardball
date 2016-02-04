#include "Systems/RenderSystem.h"
#include <unordered_map>
#include <math.h>

RenderSystem::RenderSystem():
    System()
{
    //ctor
}

RenderSystem::RenderSystem(ComponentManager* componentManager, Graphics* graphics):
    System()
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
            std::unordered_map<unsigned int, StateComponent*>::iterator stateIt = componentManager->stateComponents.find(entityID);
            if ( stateIt != componentManager->stateComponents.end() )
            {
                StateComponent* stateComponent = stateIt->second;
                this->playAnimation(deltaTime, *renderComponent, *stateComponent);
            }
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
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if (transformComponent->facing == Direction::Facing::LEFT)
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            graphics->blitSurface(renderComponent->spriteSheet, &renderComponent->sourceRect, &destinationRect, flip);
        }
    }

    return;
}

void RenderSystem::playAnimation(float deltaTime, RenderComponent& renderComponent, StateComponent& stateComponent)
{
    std::string newState = stateComponent.state;
    std::string currentAnimation = renderComponent.currentAnimation;
    bool updateSourceRect = false;
    if (newState != currentAnimation)
    {
        renderComponent.currentAnimation = newState;
        renderComponent.frameIndex = 0;
        renderComponent.timeElapsed = 0;
        updateSourceRect = true;
    }

    renderComponent.timeElapsed += deltaTime;
    std::vector<SDL_Rect> animationFrames;
    if (renderComponent.timeElapsed > renderComponent.timeToUpdate)
    {
        renderComponent.timeElapsed -= renderComponent.timeToUpdate;
        std::unordered_map<std::string, std::vector<SDL_Rect>>::iterator animIt = renderComponent.animations.find(renderComponent.currentAnimation);
        if ( animIt != renderComponent.animations.end() )
        {
            animationFrames = animIt->second;
            updateSourceRect = true;
            renderComponent.frameIndex = (renderComponent.frameIndex+1) % renderComponent.animations[renderComponent.currentAnimation].size();
        }
    }

    if (updateSourceRect && animationFrames.size() > 0)
    {
        renderComponent.sourceRect = animationFrames[renderComponent.frameIndex];
    }
}
