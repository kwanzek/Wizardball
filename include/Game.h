#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "EntityManager.h"
#include "EntityFactory.h"
#include "ComponentManager.h"
#include "Systems/RenderSystem.h"
#include "Graphics.h"

class Game
{
    public:
        Game();
        ~Game();
        void init();
        void gameLoop();
        void update(float deltaTime);
    protected:
    private:
        EntityManager* entityManager;
        EntityFactory* entityFactory;
        ComponentManager* componentManager;
        Graphics* graphics;
        RenderSystem* renderSystem;

};

#endif // GAME_H
