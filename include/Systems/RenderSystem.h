#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ComponentManager.h"

#include <iterator>

class RenderSystem
{
    public:
        RenderSystem();
        RenderSystem(ComponentManager* componentManager, Graphics* graphics);
        ~RenderSystem();
        void update(float deltaTime);
        ComponentManager* componentManager;
        Graphics* graphics;
    protected:
    private:
};

#endif // RENDERSYSTEM_H
