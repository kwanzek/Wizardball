#include "EntityFactory.h"

#include <iostream>

EntityFactory::EntityFactory()
{
    //ctor
}

EntityFactory::EntityFactory(EntityManager* entityManager, ComponentManager* componentManager):
    _entityManager(entityManager),
    _componentManager(componentManager)
{

}

EntityFactory::~EntityFactory()
{
    //dtor
}

unsigned int EntityFactory::createPlayer()
{
    unsigned int eID = _entityManager->createEntity();
    _componentManager->makeTransformComponent(eID, 300, 100);
    _componentManager->makePlayerInputComponent(eID, SDL_SCANCODE_SPACE, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
    _componentManager->makePlayerControllerComponent(eID);
    _componentManager->makeVelocityComponent(eID, 0, 0, 140, 100, 500);
    _componentManager->makeCollisionComponent(eID, 100, 100, 16, 16, CollisionLayer::PLAYER);

    //Setupanimations

    std::unordered_map<std::string, std::vector<SDL_Rect>> animations;
    std::vector<SDL_Rect> run_left;
    run_left.push_back( SDL_Rect {0, 0, 16, 16 });
    run_left.push_back( SDL_Rect {16, 0, 16, 16 });
    run_left.push_back( SDL_Rect {0, 0, 16, 16 });
    run_left.push_back( SDL_Rect {32, 0, 16, 16 });
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("run_left", run_left));

    std::vector<SDL_Rect> run_right;
    run_right.push_back( SDL_Rect {0, 16, 16, 16 });
    run_right.push_back( SDL_Rect {16, 16, 16, 16 });
    run_right.push_back( SDL_Rect {0, 16, 16, 16 });
    run_right.push_back( SDL_Rect {32, 16, 16, 16 });
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("run_right", run_right));

    std::vector<SDL_Rect> idle_left;
    idle_left.push_back( SDL_Rect {0, 0, 16, 16 });
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("idle_left", idle_left));

    std::vector<SDL_Rect> idle_right;
    idle_right.push_back( SDL_Rect {0, 16, 16, 16 });
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("idle_right", idle_right));

    _componentManager->makeRenderComponent(eID, 0, 0, 16, 16, "content/sprites/MyChar.png", true, animations);
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
