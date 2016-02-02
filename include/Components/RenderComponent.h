#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <SDL.h>
#include <SDL_Image.h>

#include <unordered_map>
#include <vector>
#include <string>

class RenderComponent
{
public:
    inline RenderComponent(
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
        sourceRect(sourceRect),
        spriteSheet(spriteSheet),
        isAnimated(isAnimated),
        animations(animations),
        currentAnimation(currentAnimation),
        timeToUpdate(timeToUpdate),
        isVisible(isVisible),
        frameIndex(frameIndex)
    {}
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

#endif // RENDERCOMPONENT_H
