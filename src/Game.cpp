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

    InputHandler* inputHandler = new InputHandler(*this);
    this->inputHandler = inputHandler;

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

    PlayerControlSystem* playerControlSystem = new PlayerControlSystem(this->componentManager, this->inputHandler);
    this->playerControlSystem = playerControlSystem;

    MovementSystem* movementSystem = new MovementSystem(this->componentManager);
    this->movementSystem = movementSystem;

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

        int currentTime = SDL_GetTicks();
        int deltaTime = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;
        this->update(deltaTime);
        events.clear();
    }
}

void Game::update(float deltaTime)
{
    inputHandler->update(this->events);
    graphics->clearRenderer();
    renderSystem->update(deltaTime);
    playerControlSystem->update(deltaTime);
    movementSystem->update(deltaTime);
    graphics->flip();
}
