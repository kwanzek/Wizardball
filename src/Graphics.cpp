#include "Graphics.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Constants.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer);
    SDL_SetWindowTitle(_window, globals::GAME_NAME.c_str());
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath)
{
    if (this->_spriteSheets.count(filePath) == 0)
    {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(
    SDL_Texture* texture,
    SDL_Rect* sourceRectangle,
    SDL_Rect* destinationRectangle,
    SDL_RendererFlip flip,
    double angle,
    SDL_Point* center
    )
{
    SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, destinationRectangle, angle, center, flip);
}

void Graphics::flip()
{
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clearRenderer()
{
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
    return this->_renderer;
}
