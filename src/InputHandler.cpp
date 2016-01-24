#include "InputHandler.h"
#include "Game.h"

InputHandler::InputHandler(Game& game):
    game(game)
{

}

InputHandler::~InputHandler()
{
    //dtor
}

void InputHandler::update(std::vector<SDL_Event>& events)
{
    for (SDL_Event event : events)
    {
        if (event.type == SDL_QUIT)
        {
                //Need to delete all the components etc. but whatever for now
                game.isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                    this->keyDownEvent(event);
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            this->keyUpEvent(event);
        }
    }
    if (this->wasKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        game.isRunning = false;
    }
}

//This function gets called at the beginning of each new frame
//to reset the keys that are no longer relevant
void InputHandler::beginNewFrame()
{
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
}

void InputHandler::keyDownEvent(SDL_Event& event)
{
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

void InputHandler::keyUpEvent(SDL_Event& event)
{
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

//check if key was pressed during this frame
bool InputHandler::wasKeyPressed(SDL_Scancode key)
{
    return this->_pressedKeys[key];
}

//check if key was released during this frame
bool InputHandler::wasKeyReleased(SDL_Scancode key)
{
    return this->_releasedKeys[key];
}

//check if key is held during this frame
bool InputHandler::isKeyHeld(SDL_Scancode key)
{
    return this->_heldKeys[key];
}
