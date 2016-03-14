#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL.h>
#include <SDL_Image.h>

#include "System.h"
#include "Graphics.h"
#include "Systems/TransformSystem.h"
#include "Systems/StateSystem.h"

#include <iterator>
#include <unordered_map>
#include <vector>
#include <string>

struct RenderComponent
{
    inline RenderComponent(
        int eid,
        SDL_Rect sourceRect,
        SDL_Texture* spriteSheet,
        bool isAnimated = false,
        std::unordered_map<std::string, std::vector<SDL_Rect>> animations =
            std::unordered_map<std::string, std::vector<SDL_Rect>>(),
        std::string currentAnimation = "",
        float timeToUpdate = 1.f,
        bool isVisible = true,
        int frameIndex = 0
    ) :
        eid(eid),
        sourceRect(sourceRect),
        spriteSheet(spriteSheet),
        isAnimated(isAnimated),
        animations(animations),
        currentAnimation(currentAnimation),
        timeToUpdate(timeToUpdate),
        isVisible(isVisible),
        frameIndex(frameIndex)
    {}
    int eid;
    SDL_Rect sourceRect;
    SDL_Texture* spriteSheet;
    bool isAnimated;
    std::unordered_map<std::string, std::vector<SDL_Rect> > animations;
    std::string currentAnimation;
    float timeToUpdate;
    bool isVisible;
    int frameIndex;
    float timeElapsed = 0.f;
};

class RenderSystem : public System
{
    public:
        RenderSystem();
        RenderSystem(Graphics* graphics, TransformSystem* transformSystem, StateSystem* stateSystem);
        ~RenderSystem();
        void update(float deltaTime);

        RenderComponent& addComponent(
            int eid,
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
        bool deleteComponent( int eid);
        bool hasComponent( int eid);
        RenderComponent& getComponent( int eid);

        void playAnimation(float deltaTime, RenderComponent& renderComponent, StateComponent& stateComponent);

        Graphics* graphics;
        TransformSystem* transformSystem;
        StateSystem* stateSystem;
        std::vector<RenderComponent> components;
        std::vector<int> handles;
    protected:
    private:
};


#endif // RENDERSYSTEM_H
