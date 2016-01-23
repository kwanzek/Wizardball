#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "EntityManager.h"
#include "ComponentManager.h"

class EntityFactory
{
    public:
        EntityFactory();
        EntityFactory(EntityManager* entityManager, ComponentManager* ComponentManager);
        virtual ~EntityFactory();
        unsigned int createPlayer();
    protected:
    private:
        EntityManager* _entityManager;
        ComponentManager* _componentManager;
};

#endif // ENTITYFACTORY_H
