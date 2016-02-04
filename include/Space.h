#ifndef SPACE_H
#define SPACE_H

#include <SDL.h>
#include "EntityFactory.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "InputHandler.h"
#include "Level.h"
#include "System.h"

#include <string>
#include <vector>

class Space
{
    public:
        Space(std::string name, InputHandler& inputHandler);
        virtual ~Space();
        EntityFactory entityFactory;
        EntityManager entityManager;
        ComponentManager componentManager;
        InputHandler inputHandler;
        Level level;

        void update(float deltaTime);
        void addSystem(System* system);

        std::string name;
        bool isActive = true;
        std::vector<System*> systems;

    protected:
    private:
};

#endif // SPACE_H
