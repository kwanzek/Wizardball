#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "EntityManager.h"
#include "EntityFactory.h"
#include "ComponentManager.h"
#include "InputHandler.h"
#include "Graphics.h"
#include "Level.h"
#include "Space.h"

#include "Systems/RenderSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"

#include <vector>

class Game
{
    public:
        Game();
        ~Game();
        void init();
        void gameLoop();
        bool isRunning;
        void loadLevel(std::string levelName, Space& space);
        void unloadLevel(Space& space);
        void setupSpaces();
        enum GameState
        {
            SPLASH,
            MAINMENU,
            GAMEPLAY
        };
    protected:
    private:
        Graphics* graphics;
        InputHandler* inputHandler;
        Level* level;
        std::vector<SDL_Event> events;
        GameState gameState;

        Space* gameplay;
        Space* mainmenu;
};

#endif // GAME_H
