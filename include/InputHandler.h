#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <map>
#include <vector>
#include "Constants.h"

class Game;

struct JoystickControls
{
    SDL_JoystickID joystickID;
    float xAxis;
    float yAxis;
    std::map<int, bool> heldButtons;
    std::map<int, bool> pressedButtons;
    std::map<int, bool> releasedButtons;
};

class InputHandler
{
    public:
        InputHandler();
        InputHandler(Game& game);
        ~InputHandler();
        void beginNewFrame();
        void keyUpEvent(SDL_Event& event);
        void keyDownEvent(SDL_Event& event);
        void joyAxisMotion(SDL_Event& event);
        void joyButtonDown(SDL_Event& event);
        void joyButtonUp(SDL_Event& event);

        float getJoyAxis(SDL_JoystickID joystickID, Axis::Axis axis);
        bool wasJoyButtonPressed(SDL_JoystickID, int button);
        bool wasJoyButtonReleased(SDL_JoystickID, int button);
        bool isJoyButtonHeld(SDL_JoystickID, int button);
        bool wasKeyPressed(SDL_Scancode key);
        bool wasKeyReleased(SDL_Scancode key);
        bool isKeyHeld(SDL_Scancode key);
        void update(std::vector<SDL_Event>& events);
        Game& game;
        std::vector<SDL_Joystick*> joysticks;
        std::vector<JoystickControls> joystickControls;

    protected:
    private:
        std::map<SDL_Scancode, bool> _heldKeys;
        std::map<SDL_Scancode, bool> _pressedKeys;
        std::map<SDL_Scancode, bool> _releasedKeys;

        //Must cross a certain threshold of input to be registered
        //The value comes in as signed int 2^32 so -32768 to 32767
        const int JOYSTICK_DEAD_ZONE = 12000;
};

#endif // INPUTHANDLER_H
