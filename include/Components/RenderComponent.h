#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <SDL.h>
#include <SDL_Image.h>

class RenderComponent
{
public:
    inline RenderComponent(SDL_Rect sourceRect, SDL_Texture* spriteSheet) :
        sourceRect(sourceRect),
        spriteSheet(spriteSheet)
    {}
    SDL_Rect sourceRect;
    SDL_Texture* spriteSheet;
};

#endif // RENDERCOMPONENT_H
