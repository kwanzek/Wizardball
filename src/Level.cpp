#include "Level.h"

#include <tinyxml2.h>
#include <SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Utils/Rectangle.h"
#include "Utils/Vector2.h"

using namespace tinyxml2;

Level::Level()
{
    //ctor
}

Level::~Level()
{
    //dtor
}

Level::Level(EntityFactory* entityFactory, Graphics* graphics) :
    entityFactory(entityFactory),
    graphics(graphics)
{

}

void Level::loadLevel(std::string mapName)
{
    //Parse the .tmx file
    XMLDocument doc;
    std::stringstream xmlStringStream;
    xmlStringStream << "content/maps/" << mapName << ".tmx";
    doc.LoadFile(xmlStringStream.str().c_str());

    XMLElement* mapNode = doc.FirstChildElement("map");

    //Get the width and height of the whole map
    int width;
    int height;

    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);

    //Get the width and height of the tiles
    int tileWidth;
    int tileHeight;

    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);

    //Loading the tileset
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL)
    {
        while (pTileset)
        {
            int firstgid;
            const char* sourceName = pTileset->Attribute("name");

            std::stringstream tilesetStream;
            tilesetStream << "content/tilesets/" << sourceName << ".png";
            tilesetName = tilesetStream.str();
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics->getRenderer(), graphics->loadImage(tilesetStream.str()));

            tileset = texture;

            //Just one for now
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }

   //Loading the layers
    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != NULL)
    {
        while(pLayer)
        {
            //Loading the data element
            XMLElement* pData = pLayer->FirstChildElement("data");
            if (pData != NULL)
            {
                while(pData)
                {
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if (pTile != NULL)
                    {
                        int tileCounter = 0;
                        while (pTile)
                        {
                            int gid = pTile->IntAttribute("gid");

                            //Build each individual tile here
                            //If gid is zero, no tile should be drawn
                            if (gid == 0)
                            {
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile"))
                                {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else
                                {
                                    break;
                                }
                            }

                            //Get the position of the tile in the level
                            int tileX = 0;
                            int tileY = 0;
                            tileX = tileCounter % width;
                            tileX *= tileWidth;

                            //Go across the X horizontally, then increase tileY by 16, etc.
                            //tileCounter = 40 / width = 20 = 2 * 16 tileHeight means Y = 32
                            tileY += tileHeight * (tileCounter / width);
                            Vector2 finalTilePosition = Vector2(tileX, tileY);

                            //Calculate the position of the tile in the tileset
                            int tilesetWidth = 256;
                            int tilesetX = (gid % (tilesetWidth / tileWidth) - 1) * tileWidth;
                            int tilesetY = tileHeight * (gid / (tilesetWidth / tileWidth));

                            Vector2 finalTilesetPosition = Vector2(tilesetX, tilesetY);
                            entityFactory->createTile(tilesetName, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                            tileCounter++;

                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }



                    pData = pData->NextSiblingElement("data");
                }
            }

            pLayer = pLayer->NextSiblingElement("layer");
        }
    }

}
