#include "InputHandler.h"
#include "Game.h"
#include <cmath>

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
        else if (event.type == SDL_JOYAXISMOTION)
        {
            this->joyAxisMotion(event);
        }
        else if (event.type == SDL_JOYBUTTONDOWN)
        {
            this->joyButtonDown(event);
        }
        else if (event.type == SDL_JOYBUTTONUP)
        {
            this->joyButtonUp(event);
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
    for (unsigned int i = 0; i < this->joystickControls.size(); ++i)
    {
        this->joystickControls[i].pressedButtons.clear();
        this->joystickControls[i].releasedButtons.clear();
        //this->joystickControls[i].xAxis = 0.0f;
        //this->joystickControls[i].yAxis = 0.0f;
    }
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

void InputHandler::joyAxisMotion(SDL_Event& event)
{
    SDL_JoystickID joystickID = event.jaxis.which;
    int axis = static_cast<int>(event.jaxis.axis);
    int value = static_cast<int>(event.jaxis.value);
    if (std::abs(value) < JOYSTICK_DEAD_ZONE )
    {
        //X axis
        if (axis == 0)
        {
            this->joystickControls[joystickID].xAxis = value;
        }
        else if (axis == 1)
        {
            this->joystickControls[joystickID].yAxis = value;
        }
    }
    else
    {
        if (axis == 0)
        {
            this->joystickControls[joystickID].xAxis = 0.0f;
        }
        else if (axis == 1)
        {
            this->joystickControls[joystickID].yAxis = 0.0f;
        }
    }
}

void InputHandler::joyButtonDown(SDL_Event& event)
{
    SDL_JoystickID joystickID = event.jbutton.which;
    int button = static_cast<int>(event.jbutton.button);
    this->joystickControls[joystickID].pressedButtons[button] = true;
    this->joystickControls[joystickID].heldButtons[button] = true;
}

void InputHandler::joyButtonUp(SDL_Event& event)
{
    SDL_JoystickID joystickID = event.jbutton.which;
    int button = static_cast<int>(event.jbutton.button);
    this->joystickControls[joystickID].releasedButtons[button] = true;
    this->joystickControls[joystickID].heldButtons[button] = false;
}

float InputHandler::getJoyAxis(SDL_JoystickID joystickID, Axis axis)
{
    //We are storing the axes as 0 and 1 like SDL, but we want to reason about them
    //with an enum rather than passing magic ints around
    //In the future, since R and L trigger on XBOX controllers are treated like axes
    //As well as the right stick, we might want to extend this further
    float axisVal = 0;
    if (axis == Axis::YAXIS)
    {
        axisVal = this->joystickControls[joystickID].yAxis;
    }
    else if (axis == Axis::XAXIS)
    {
        axisVal = this->joystickControls[joystickID].xAxis;
    }
    return axisVal;
}

bool InputHandler::wasJoyButtonPressed(SDL_JoystickID joystickID, int button)
{
    return this->joystickControls[joystickID].pressedButtons[button];
}

bool InputHandler::wasJoyButtonReleased(SDL_JoystickID joystickID, int button)
{
    return this->joystickControls[joystickID].releasedButtons[button];
}

bool InputHandler::isJoyButtonHeld(SDL_JoystickID joystickID, int button)
{
    return this->joystickControls[joystickID].heldButtons[button];
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
