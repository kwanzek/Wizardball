#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ComponentManager.h"

#include <iterator>
#include <map>

class RenderSystem
{
    public:
        RenderSystem();
        RenderSystem(ComponentManager* componentManager, Graphics* graphics);
        virtual ~RenderSystem();
        virtual void update(float elapsedTime);
        ComponentManager* componentManager;
        Graphics* graphics;
    protected:
    private:
};

#endif // RENDERSYSTEM_H
