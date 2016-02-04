#include "Space.h"

Space::Space(std::string name, InputHandler& inputHandler):
    inputHandler(inputHandler)
{

}

Space::~Space()
{
    //dtor
}

void Space::update(float deltaTime)
{
    if (isActive)
    {
        for (unsigned int i = 0; i < systems.size(); ++i)
        {
            systems[i]->update(deltaTime);
        }
    }
}

void Space::addSystem(System* system)
{
    systems.push_back(system);
}
