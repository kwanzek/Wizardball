#include "EntityFactory.h"

#include <iostream>

EntityFactory::EntityFactory()
{
    //ctor
}

EntityFactory::EntityFactory(
    EntityManager* entityManager,
    InputHandler* inputHandler,
    CollisionSystem* collisionSystem,
    MovementSystem* movementSystem,
    PlayerControlSystem* playerControlSystem,
    PlayerInputSystem* playerInputSystem,
    RenderSystem* renderSystem,
    StateSystem* stateSystem,
    TransformSystem* transformSystem
):
    entityManager(entityManager),
    inputHandler(inputHandler),
    collisionSystem(collisionSystem),
    movementSystem(movementSystem),
    playerControlSystem(playerControlSystem),
    playerInputSystem(playerInputSystem),
    renderSystem(renderSystem),
    stateSystem(stateSystem),
    transformSystem(transformSystem)
{

}

EntityFactory::~EntityFactory()
{
    //dtor
}

int EntityFactory::createPlayer()
{
    int eID = entityManager->createEntity();

    transformSystem->addComponent(eID, 350, 100);

    //This should be handled more organically to allow for more players
    //And it would be nice if it could be handled during gameplay rather than just player creation
    //But for now, just getting something in there
    SDL_JoystickID player1joystick = -1;
    if (inputHandler->joystickControls.size() > 0)
    {
        player1joystick = inputHandler->joystickControls[0].joystickID;
    }
    playerInputSystem->addComponent(
        eID,
        SDL_SCANCODE_SPACE,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_Z,
        SDL_SCANCODE_C,
        player1joystick,
        0,
        1,
        2
    );

    playerControlSystem->addComponent(eID);
    movementSystem->addComponent(eID, 0, 0, 140, 100, 500);
    collisionSystem->addComponent(eID, 350, 100, 16, 16, CollisionLayer::PLAYER);

    //Setup animations

    std::unordered_map<std::string, std::vector<SDL_Rect>> animations;
    std::vector<SDL_Rect> run;
    run.push_back( SDL_Rect {0, 16, 16, 16 });
    run.push_back( SDL_Rect {16, 16, 16, 16 });
    run.push_back( SDL_Rect {0, 16, 16, 16 });
    run.push_back( SDL_Rect {32, 16, 16, 16 });
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("run", run));

    std::vector<SDL_Rect> idle;
    idle.push_back( SDL_Rect {0, 16, 16, 16 });
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("idle", idle));

    renderSystem->addComponent(eID, 0, 16, 16, 16, "content/sprites/MyChar.png", true, animations, "idle", .1f);
    stateSystem->addComponent(eID, "idle");
    return eID;
}

int EntityFactory::createTile(std::string texturePath, Vector2 vecSize, Vector2 tilesetPosition, Vector2 tilePosition)
{
    int eID = entityManager->createEntity();
    transformSystem->addComponent(eID, tilePosition.x, tilePosition.y);
    renderSystem->addComponent(eID, tilesetPosition.x, tilesetPosition.y, vecSize.x, vecSize.y, texturePath);
    collisionSystem->addComponent(eID, tilePosition.x, tilePosition.y, vecSize.x, vecSize.y, CollisionLayer::TILE);
    return eID;
}

int EntityFactory::createFireball(Vector2 position, float dx, float dy )
{
    int eID = entityManager->createEntity();
    transformSystem->addComponent(eID, position.x, position.y);
    renderSystem->addComponent(eID, 0, 0, 16, 16, "content/sprites/Fireball.png");
    movementSystem->addComponent(eID, dx, dy, 100, 100, 100);
    collisionSystem->addComponent(eID, position.x, position.y, 16,16, CollisionLayer::PROJECTILE);
    return eID;
}

int EntityFactory::createBall()
{
    int eID = entityManager->createEntity();
    transformSystem->addComponent(eID, 150, 150);
    renderSystem->addComponent(eID, 0, 0, 16, 16, "content/sprites/Ball.png");
    movementSystem->addComponent(eID, 0, 0, 0, 100, 100);
    collisionSystem->addComponent(eID, 150, 150, 16, 16, CollisionLayer::BALL);
    return eID;
}
