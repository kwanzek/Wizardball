#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <map>
#include <vector>

class Game;

class InputHandler
{
    public:
        InputHandler();
        InputHandler(Game& game);
        ~InputHandler();
        void beginNewFrame();
        void keyUpEvent(SDL_Event& event);
        void keyDownEvent(SDL_Event& event);
        bool wasKeyPressed(SDL_Scancode key);
        bool wasKeyReleased(SDL_Scancode key);
        bool isKeyHeld(SDL_Scancode key);
        void update(std::vector<SDL_Event>& events);
        Game& game;

    protected:
    private:
        std::map<SDL_Scancode, bool> _heldKeys;
        std::map<SDL_Scancode, bool> _pressedKeys;
        std::map<SDL_Scancode, bool> _releasedKeys;
};

#endif // INPUTHANDLER_H
