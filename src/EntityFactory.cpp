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
    return eID;
}
