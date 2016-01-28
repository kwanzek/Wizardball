#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "EntityFactory.h"

struct SDL_Rect;
struct SDL_Texture;

class Level
{
    public:
        Level();
        Level(EntityFactory* entityFactory, Graphics* graphics);
        ~Level();
        void loadLevel(std::string mapName);
        EntityFactory* entityFactory;
        Graphics* graphics;
        SDL_Texture* tileset;
        std::string tilesetName;
    protected:
    private:
};

#endif // LEVEL_H
