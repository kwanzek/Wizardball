#include "Systems/RenderSystem.h"
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <assert.h>

RenderSystem::RenderSystem():
    System()
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles.push_back(-1);
    }
}

RenderSystem::RenderSystem(Graphics* graphics, TransformSystem* transformSystem, StateSystem* stateSystem):
    System(),
    graphics(graphics),
    transformSystem(transformSystem),
    stateSystem(stateSystem)
{
    components.reserve(65535);
    handles.reserve(65535);
    for (unsigned int i = 0; i < handles.capacity(); ++i)
    {
        handles[i] = -1;
    }
}

RenderSystem::~RenderSystem()
{
    //dtor
}


void RenderSystem::update(float deltaTime)
{
    for (unsigned int i = 0; i < this->components.size(); ++i)
    {

        RenderComponent& renderComponent = components[i];
        int eid = renderComponent.eid;
        if (renderComponent.isAnimated && stateSystem->hasComponent(eid))
        {
            StateComponent& stateComponent = stateSystem->getComponent(eid);
            this->playAnimation(deltaTime, renderComponent, stateComponent);
        }
        if (transformSystem->hasComponent(eid))
        {
            TransformComponent& transformComponent = transformSystem->getComponent(eid);
            SDL_Rect destinationRect = {
                static_cast<int>(ceil(transformComponent.x)),
                static_cast<int>(ceil(transformComponent.y)),
                static_cast<int>(ceil(renderComponent.sourceRect.w)),
                static_cast<int>(ceil(renderComponent.sourceRect.h))
            };
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if (transformComponent.facing == Direction::Facing::LEFT)
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            graphics->blitSurface(renderComponent.spriteSheet, &renderComponent.sourceRect, &destinationRect, flip);
        }
    }
    return;
}

RenderComponent& RenderSystem::addComponent(
    int eid,
    int x,
    int y,
    int width,
    int height,
    std::string texturePath,
    bool animated,
    std::unordered_map<std::string, std::vector<SDL_Rect>> animations,
    std::string currentAnimation,
    float timeToUpdate
)
{
    SDL_Rect sourceRect = { x, y, width, height };
    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(graphics->getRenderer(), graphics->loadImage(texturePath));
    components.emplace_back(
        eid,
        sourceRect,
        spriteSheet,
        animated,
        animations,
        currentAnimation,
        timeToUpdate
    );
    handles[eid] = components.size()-1;
    return components.at(components.size()-1);
}

bool RenderSystem::deleteComponent(int eid)
{
    if (eid < handles.capacity())
    {
        int index = handles[eid];
        components[index] = components[components.size()-1];
        components.pop_back();
        handles[components[index].eid] = index;
        handles[eid] = -1;
        return true;
    }
    return false;
}

bool RenderSystem::hasComponent(int eid)
{
    if (eid < handles.capacity())
    {
        return handles[eid] != -1;
    }
    return false;
}

RenderComponent& RenderSystem::getComponent(int eid)
{
    assert (eid < handles.capacity() && this->hasComponent(eid));
    return components[handles[eid]];
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
