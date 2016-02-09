#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "EntityManager.h"
#include "ComponentManager.h"
#include "InputHandler.h"
#include "Utils/Vector2.h"

#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

class EntityFactory
{
    public:
        EntityFactory();
        EntityFactory(EntityManager* entityManager, ComponentManager* ComponentManager, InputHandler* inputHandler);
        virtual ~EntityFactory();
        unsigned int createPlayer();
        unsigned int createTile(std::string texturePath, Vector2 vecSize, Vector2 tilesetPosition, Vector2 tilePosition);
        unsigned int createFireball(Vector2 position, float dx, float dy);
        unsigned int createBall();
    protected:
    private:
        EntityManager* _entityManager;
        ComponentManager* _componentManager;
        InputHandler* _inputHandler;
};

#endif // ENTITYFACTORY_H
