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
    int numJoysticks = SDL_NumJoysticks();
    if (numJoysticks > 0)
    {
        for (int i = 0; i < numJoysticks; ++i)
        {
            this->inputHandler->joysticks.push_back(SDL_JoystickOpen(i));
            this->inputHandler->joystickControls.push_back(JoystickControls());
            this->inputHandler->joystickControls[i].joystickID = SDL_JoystickInstanceID(inputHandler->joysticks[i]);
        }
    }

    Graphics* graphics = new Graphics();
    this->graphics = graphics;

    this->setupSpaces();
}

void Game::gameLoop()
{
    SDL_Event event;
    gameplay->entityFactory.createPlayer();
    gameplay->entityFactory.createBall();
    this->loadLevel("test", *gameplay);

    float dt = 0.01f;
    float accumulator = 0.f;

    int currentTimeMS = SDL_GetTicks();
    int lastUpdateTimeMS = currentTimeMS;

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
                gameplay->update(dt);
            }
            else if (gameState == GameState::MAINMENU)
            {
                mainmenu->update(dt);
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
        if (gameState == GameState::GAMEPLAY)
        {
            gameplay->renderSystem->update(deltaTime);
        }
        else
        {
            mainmenu->renderSystem->update(deltaTime);
        }
        graphics->flip();

    }
}

void Game::setupSpaces()
{
    //Set up gameplay space
    this->gameplay = new Space("GAMEPLAY", *this->inputHandler);
    this->gameplay->entityManager = EntityManager();
    this->gameplay->componentManager = ComponentManager(this->graphics);
    this->gameplay->entityFactory = EntityFactory(
        &this->gameplay->entityManager,
        &this->gameplay->componentManager,
        this->inputHandler
    );

    gameplay->addSystem(new PlayerControlSystem(&gameplay->componentManager, &gameplay->entityFactory, this->inputHandler));
    gameplay->addSystem(new CollisionSystem(&gameplay->componentManager));
    gameplay->addSystem(new MovementSystem(&gameplay->componentManager));
    gameplay->renderSystem = new RenderSystem(&gameplay->componentManager, this->graphics);

    //Set up menu
    this->mainmenu = new Space("MAINMENU", *this->inputHandler);
    this->mainmenu->entityManager = EntityManager();
    this->mainmenu->componentManager = ComponentManager(this->graphics);
    this->mainmenu->entityFactory = EntityFactory(
        &this->mainmenu->entityManager,
        &this->mainmenu->componentManager,
        this->inputHandler
    );

    mainmenu->renderSystem = new RenderSystem(&mainmenu->componentManager, this->graphics);
}

void Game::loadLevel(std::string levelName, Space& space)
{
    this->unloadLevel(space);
    space.level = Level(&space.entityFactory, this->graphics);
    space.level.loadLevel(levelName);
}

void Game::unloadLevel(Space& space)
{

}
