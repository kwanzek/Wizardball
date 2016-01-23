#include "Game.h"

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
}

void Game::gameLoop()
{
    SDL_Event event;
    int lastUpdateTime = SDL_GetTicks();
    entityFactory->createPlayer();
    while(true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                //Need to delete all the components etc. but whatever for now
                return;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    return;
                }
            }
        }
        const int currentTime = SDL_GetTicks();
        int elaspedTime = currentTime - lastUpdateTime;
        this->update(elaspedTime);
    }
}

void Game::update(float deltaTime)
{
    graphics->clearRenderer();
    renderSystem->update(deltaTime);
    graphics->flip();
}
