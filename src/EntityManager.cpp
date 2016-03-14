#include "EntityManager.h"
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

int EntityManager::createEntity()
{
     int eID = this->getID();
    this->entities.push_back(eID);
    return eID;
}

 int EntityManager::getID()
{
    unsigned int temp = _previousID;
    _previousID++;
    if (_previousID == UINT_MAX)
    {
        _previousID = 0;
    }
    return temp;
}
