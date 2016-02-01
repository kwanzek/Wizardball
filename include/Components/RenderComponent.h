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
        int frameIndex = 0,
        float timeElapsed = 0.f,
        bool isVisible = true
    ) :
        sourceRect(sourceRect),
        spriteSheet(spriteSheet),
        isAnimated(isAnimated),
        animations(animations),
        frameIndex(frameIndex),
        timeElapsed(timeElapsed),
        isVisible(isVisible)
    {}
    SDL_Rect sourceRect;
    SDL_Texture* spriteSheet;
    bool isAnimated;
    std::unordered_map<std::string, std::vector<SDL_Rect> > animations;

    int frameIndex;
    float timeElapsed;
    bool isVisible;

};

#endif // RENDERCOMPONENT_H
