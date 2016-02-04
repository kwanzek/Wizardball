#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ComponentManager.h"
#include "System.h"

#include <iterator>

class RenderSystem : public System
{
    public:
        RenderSystem();
        RenderSystem(ComponentManager* componentManager, Graphics* graphics);
        ~RenderSystem();
        void update(float deltaTime);
        void playAnimation(float deltaTime, RenderComponent& renderComponent, StateComponent& stateComponent);
        Graphics* graphics;
    protected:
    private:
};

#endif // RENDERSYSTEM_H
