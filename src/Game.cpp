#include "Game.h"
#include <iostream>
#include <cmath>
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
    gameState = GameState::GAMEPLAY;

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

    PlayerControlSystem* playerControlSystem = new PlayerControlSystem(this->componentManager, this->entityFactory, this->inputHandler);
    this->playerControlSystem = playerControlSystem;

    MovementSystem* movementSystem = new MovementSystem(this->componentManager);
    this->movementSystem = movementSystem;

    CollisionSystem* collisionSystem = new CollisionSystem(this->componentManager);
    this->collisionSystem = collisionSystem;

}

void Game::gameLoop()
{
    SDL_Event event;
    entityFactory->createPlayer();
    this->loadLevel("test");

    float dt = 0.01f;
    float accumulator = 0.f;

    int currentTimeMS = SDL_GetTicks();
    int lastUpdateTimeMS = currentTimeMS;

    //This isn't the final implementation, each space should have their own specific version of a system
    Space gameplay = Space("GAMEPLAY", *this->inputHandler);
    gameplay.addSystem(this->playerControlSystem);
    gameplay.addSystem(this->collisionSystem);
    gameplay.addSystem(this->movementSystem);
    //gameplay.addSystem(this->renderSystem);
    Space mainmenu = Space("MAINMENU", *this->inputHandler);
    //gameplay.addSystem(this->renderSystem);

    while(this->isRunning)
    {

        lastUpdateTimeMS = currentTimeMS;
        currentTimeMS = SDL_GetTicks();
        float deltaTime = std::min((currentTimeMS - lastUpdateTimeMS) / 1000.0f, 0.016f);
        accumulator += deltaTime;

        while (accumulator >= dt)
        {
            while (SDL_PollEvent(&event) !=0)
            {
                this->events.push_back(event);
            }
            inputHandler->update(this->events);
            if (gameState == GameState::GAMEPLAY)
            {
                gameplay.update(dt);
            }
            else if (gameState == GameState::MAINMENU)
            {
                mainmenu.update(dt);
            }
            if (inputHandler->wasKeyPressed(SDL_SCANCODE_1))
            {
                if (gameState == GameState::GAMEPLAY)
                {
                    gameState = GameState::MAINMENU;
                }
                else if (gameState == GameState::MAINMENU)
                {
                    gameState = GameState::GAMEPLAY;
                }
            }
            inputHandler->beginNewFrame();
            events.clear();
            accumulator -= dt;
        }
        //For now the game is fast enough that I don't need to worry about interpolating the graphics, I can just render them
        //But later I will need to figure out how to integrate state properly, likely holding an Int that is "numStateUpdates"
        //And then I can get the alpha between this state and the next state with the rest of accumulator
        graphics->clearRenderer();
        renderSystem->update(deltaTime);
        graphics->flip();

    }
}

void Game::update(float deltaTime)
{


    graphics->clearRenderer();


    renderSystem->update(deltaTime);


    graphics->flip();
}

void Game::loadLevel(std::string levelName)
{
    this->unloadLevel();
    level = new Level(this->entityFactory, this->graphics);
    level->loadLevel(levelName);
}

void Game::unloadLevel()
{

}
