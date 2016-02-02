#ifndef GRAPHICS_H
#define GRAPHICS_H

/* Graphics
*   Used to display all images for game
*/

#include <SDL.h>
#include <unordered_map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();

    /* SDL_Surface* loadImage
    * Loads an image into the _spriteSheets map if it does not already exist
    * Returns the image
    */
    SDL_Surface* loadImage(const std::string &filepath);

    /* void blitSurface
    * Draws a texture to a certain part of the screen
    */
    void blitSurface(
        SDL_Texture* source,
        SDL_Rect* sourceRectangle,
        SDL_Rect* destinationRectangle,
        SDL_RendererFlip flip = SDL_FLIP_NONE,
        double angle = 0.0,
        SDL_Point* center = NULL
    );

    /* void flip
    * Renders everything to the screen
    */
    void flip();

    /* void clearRenderer
    * Clears the screen
    */
    void clearRenderer();

    /* SDL_Renderer* getRenderer
    * Return the renderer
    */
    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    std::unordered_map<std::string, SDL_Surface*> _spriteSheets;
};

#endif // GRAPHICS_H
