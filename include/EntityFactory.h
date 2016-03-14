#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "EntityManager.h"
#include "InputHandler.h"
#include "Utils/Vector2.h"

#include "Systems/CollisionSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/StateSystem.h"
#include "Systems/TransformSystem.h"

#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

class PlayerControlSystem;
class EntityFactory
{
    public:
        EntityFactory();
        EntityFactory(
            EntityManager* entityManager,
            InputHandler* inputHandler,
            CollisionSystem* collisionSystem,
            MovementSystem* movementSystem,
            PlayerControlSystem* playerControlSystem,
            PlayerInputSystem* playerInputSystem,
            RenderSystem* renderSystem,
            StateSystem* stateSystem,
            TransformSystem* transformSystem
        );
        virtual ~EntityFactory();
        int createPlayer();
        int createTile(std::string texturePath, Vector2 vecSize, Vector2 tilesetPosition, Vector2 tilePosition);
        int createFireball(Vector2 position, float dx, float dy);
        int createBall();
    protected:
    private:
        EntityManager* entityManager;
        InputHandler* inputHandler;
        CollisionSystem* collisionSystem;
        MovementSystem* movementSystem;
        PlayerControlSystem* playerControlSystem;
        PlayerInputSystem* playerInputSystem;
        RenderSystem* renderSystem;
        StateSystem* stateSystem;
        TransformSystem* transformSystem;

};

#endif // ENTITYFACTORY_H
