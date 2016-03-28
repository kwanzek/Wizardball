#include "Game.h"
#include <iostream>
#include <cmath>

#define DEBUG_MODE true

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

    #if DEBUG_MODE
    bool pauseTicks = false;
    bool advanceOneTick = false;
    #endif // DEBUG_MODE

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

                #if DEBUG_MODE
                if (event.key.keysym.scancode == SDL_SCANCODE_5 && event.type == SDL_KEYDOWN)
                {
                    advanceOneTick = true;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_4 && event.type == SDL_KEYDOWN)
                {
                    pauseTicks = !pauseTicks;
                }
                #endif // DEBUG_MODE

                this->events.push_back(event);
            }

            inputHandler->update(this->events);

            #if DEBUG_MODE
            if (pauseTicks && !advanceOneTick)
            {
                continue;
            }
            advanceOneTick = false;
            #endif // DEBUG_MODE

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
                    //gameState = GameState::MAINMENU;
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

    TransformSystem* gameplayTransformSystem = new TransformSystem();
    StateSystem* gameplayStateSystem = new StateSystem();
    PlayerInputSystem* gameplayPIS = new PlayerInputSystem();
    MovementSystem* gameplayMovementSystem = new MovementSystem(gameplayTransformSystem);
    PickupSystem* gameplayPickupSystem = new PickupSystem(gameplayTransformSystem, gameplayMovementSystem);
    RenderSystem* gameplayRenderSystem = new RenderSystem(this->graphics, gameplayTransformSystem, gameplayStateSystem);
    PlayerControlSystem* gameplayPCS = new PlayerControlSystem(
        this->inputHandler,
        gameplayTransformSystem,
        gameplayMovementSystem,
        gameplayStateSystem,
        gameplayPIS,
        gameplayPickupSystem
    );
    CollisionSystem* gameplayCollisionSystem = new CollisionSystem(gameplayTransformSystem, gameplayMovementSystem, gameplayPCS);


    gameplay->addSystem(gameplayTransformSystem);
    gameplay->addSystem(gameplayStateSystem);
    gameplay->addSystem(gameplayPIS);
    gameplay->addSystem(gameplayPCS);
    gameplay->addSystem(gameplayCollisionSystem);
    gameplay->addSystem(gameplayPickupSystem);
    gameplay->addSystem(gameplayMovementSystem);
    gameplay->renderSystem = gameplayRenderSystem;

    this->gameplay->entityFactory = EntityFactory(
        &this->gameplay->entityManager,
        this->inputHandler,
        gameplayCollisionSystem,
        gameplayMovementSystem,
        gameplayPCS,
        gameplayPIS,
        gameplayRenderSystem,
        gameplayStateSystem,
        gameplayTransformSystem
    );

    gameplayPCS->entityFactory = &this->gameplay->entityFactory;
    gameplayPickupSystem->collisionSystem = gameplayCollisionSystem;
    //Set up menu
    /*
    this->mainmenu = new Space("MAINMENU", *this->inputHandler);
    this->mainmenu->entityManager = EntityManager();
    this->mainmenu->entityFactory = EntityFactory(
        &this->mainmenu->entityManager,
        this->inputHandler
    );

    TransformSystem menuTransformSystem = new TransformSystem();

    mainmenu->addSystem(menuTransformSystem);
    mainmenu->renderSystem = new RenderSystem(this->graphics, *menuTransformSystem);*/
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
