#include "Game.h"
#include <iostream>

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    isRunning = true;

    EntityManager* entityManager = new EntityManager();
    this->entityManager = entityManager;

    Graphics* graphics = new Graphics();
    this->graphics = graphics;

    ComponentManager* componentManager = new ComponentManager(graphics);
    this->componentManager = componentManager;

    EntityFactory* entityFactory = new EntityFactory(entityManager, componentManager);
    this->entityFactory = entityFactory;

    RenderSystem* renderSystem = new RenderSystem(this->componentManager, this->graphics);
    this->renderSystem = renderSystem;

    InputHandler* inputHandler = new InputHandler(*this);
    this->inputHandler = inputHandler;
}

void Game::gameLoop()
{
    SDL_Event event;
    int lastUpdateTime = SDL_GetTicks();
    entityFactory->createPlayer();

    while(this->isRunning)
    {

        while (SDL_PollEvent(&event) !=0)
        {
            this->events.push_back(event);
        }

        const int currentTime = SDL_GetTicks();
        int elaspedTime = currentTime - lastUpdateTime;
        this->update(elaspedTime);
        events.clear();
    }
}

void Game::update(float deltaTime)
{
    inputHandler->update(this->events);
    graphics->clearRenderer();
    renderSystem->update(deltaTime);
    graphics->flip();
}
