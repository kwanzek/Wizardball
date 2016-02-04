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
        void update(float deltaTime);
        bool isRunning;
        void loadLevel(std::string levelName);
        void unloadLevel();
        enum GameState
        {
            SPLASH,
            MAINMENU,
            GAMEPLAY
        };
    protected:
    private:
        EntityManager* entityManager;
        EntityFactory* entityFactory;
        ComponentManager* componentManager;
        Graphics* graphics;
        RenderSystem* renderSystem;
        PlayerControlSystem* playerControlSystem;
        MovementSystem* movementSystem;
        CollisionSystem* collisionSystem;
        InputHandler* inputHandler;
        Level* level;
        std::vector<SDL_Event> events;
        GameState gameState;
};

#endif // GAME_H
