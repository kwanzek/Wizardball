#include "EntityFactory.h"

#include <iostream>

EntityFactory::EntityFactory()
{
    //ctor
}

EntityFactory::EntityFactory(EntityManager* entityManager, ComponentManager* componentManager, InputHandler* inputHandler):
    _entityManager(entityManager),
    _componentManager(componentManager),
    _inputHandler(inputHandler)
{

}

EntityFactory::~EntityFactory()
{
    //dtor
}

unsigned int EntityFactory::createPlayer()
{
    unsigned int eID = _entityManager->createEntity();
    _componentManager->makeTransformComponent(eID, 350, 100);

    //This should be handled more organically to allow for more players
    //And it would be nice if it could be handled during gameplay rather than just player creation
    //But for now, just getting something in there
    SDL_JoystickID player1joystick = -1;
    if (_inputHandler->joystickControls.size() > 0)
    {
        player1joystick = _inputHandler->joystickControls[0].joystickID;
    }
    _componentManager->makePlayerInputComponent(
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

    _componentManager->makePlayerControllerComponent(eID);
    _componentManager->makeVelocityComponent(eID, 0, 0, 140, 100, 500);
    _componentManager->makeCollisionComponent(eID, 100, 100, 16, 16, CollisionLayer::PLAYER);

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

    _componentManager->makeRenderComponent(eID, 0, 0, 16, 16, "content/sprites/MyChar.png", true, animations, "idle", .1f);
    _componentManager->makeStateComponent(eID, "idle");
    return eID;
}

unsigned int EntityFactory::createTile(std::string texturePath, Vector2 vecSize, Vector2 tilesetPosition, Vector2 tilePosition)
{
    unsigned int eID = _entityManager->createEntity();
    _componentManager->makeTransformComponent(eID, tilePosition.x, tilePosition.y);
    _componentManager->makeRenderComponent(eID, tilesetPosition.x, tilesetPosition.y, vecSize.x, vecSize.y, texturePath);
    _componentManager->makeCollisionComponent(eID, tilePosition.x, tilePosition.y, vecSize.x, vecSize.y, CollisionLayer::TILE);
    return eID;
}

unsigned int EntityFactory::createFireball(Vector2 position, float dx, float dy )
{
    unsigned int eID = _entityManager->createEntity();
    _componentManager->makeTransformComponent(eID, position.x, position.y);
    _componentManager->makeRenderComponent(eID, 0, 0, 16, 16, "content/sprites/Fireball.png");
    _componentManager->makeVelocityComponent(eID, dx, dy);
    _componentManager->makeCollisionComponent(eID, position.x, position.y, 16,16, CollisionLayer::PROJECTILE);
    return eID;
}

unsigned int EntityFactory::createBall()
{
    unsigned int eID = _entityManager->createEntity();
    _componentManager->makeTransformComponent(eID, 150, 150);
    _componentManager->makeRenderComponent(eID, 0, 0, 16, 16, "content/sprites/Ball.png");
    _componentManager->makeVelocityComponent(eID, 0, 0, 0, 100, 100);
    _componentManager->makeCollisionComponent(eID, 150, 150, 16, 16, CollisionLayer::BALL);
    return eID;
}
