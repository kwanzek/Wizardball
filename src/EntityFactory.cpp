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
    _componentManager->makeTransformComponent(eID, 100, 100);
    _componentManager->makeRenderComponent(eID, 0, 0, 16, 16, "content/sprites/MyChar.png");
    _componentManager->makePlayerInputComponent(eID, SDL_SCANCODE_SPACE, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
    _componentManager->makePlayerControllerComponent(eID);
    _componentManager->makeVelocityComponent(eID, 0, 0, 0.25, 0.15, 0.25);
    return eID;
}

unsigned int EntityFactory::createTile(std::string texturePath, Vector2 vecSize, Vector2 tilesetPosition, Vector2 tilePosition)
{
    unsigned int eID = _entityManager->createEntity();
    _componentManager->makeTransformComponent(eID, tilePosition.x, tilePosition.y);
    _componentManager->makeRenderComponent(eID, tilesetPosition.x, tilesetPosition.y, vecSize.x, vecSize.y, texturePath);
    return eID;
}
