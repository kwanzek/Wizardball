#include "EntityManager.h"
#include "Entity.h"
#include <climits>
#include <iostream>

EntityManager::EntityManager() :
    _previousID(0)
{
    //ctor
}

EntityManager::~EntityManager()
{
    //dtor
}

unsigned int EntityManager::createEntity()
{
    unsigned int eID = this->getID();
    this->entities.push_back(eID);
    return eID;
}

unsigned int EntityManager::getID()
{
    if (_previousID == UINT_MAX)
    {
        _previousID = 0;
    }
    _previousID++;
    return _previousID;
}
