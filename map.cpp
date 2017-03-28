#include "map.h"
#include "Constants.h"
#include <iostream>
#include "Tile.h"

// public methods
Map::Map(int widthTilesNumber, int heightTilesNumber) : widthTilesNumber(widthTilesNumber), heightTilesNumber(heightTilesNumber)
{
    // Przydzielamy pamiec dla tablicy przechowujacej plytki mapy
    mapTable = new Tile[widthTilesNumber * heightTilesNumber];

    generateMap();

    // Ladujemy tileset mapy
    if(!mapTileset.loadFromFile("Graphics/Map/map.png"))
    {

    }

    // Zmieniamy rozmiar dynamicznej tablicy wierzcholkow
    mapVertices.setPrimitiveType(sf::Quads);
    mapVertices.resize(widthTilesNumber * heightTilesNumber * 4);

    for(int i = 0; i < heightTilesNumber; ++i)
    {
        for(int j = 0; j < widthTilesNumber; ++j)
        {
            int tileIndex = static_cast<int>(mapTable[i * widthTilesNumber + j].getType());

            int textureCoordinateX = tileIndex % (mapTileset.getSize().x / Constants::TILE_WIDTH);
            int textureCoordinateY = tileIndex / (mapTileset.getSize().x / Constants::TILE_WIDTH);

            sf::Vertex* currentQuad = &mapVertices[(i * widthTilesNumber + j) * 4];

            currentQuad[0].position = sf::Vector2f(j * Constants::TILE_WIDTH, i * Constants::TILE_HEIGHT);
            currentQuad[1].position = sf::Vector2f((j+1) * Constants::TILE_WIDTH, i * Constants::TILE_HEIGHT);
            currentQuad[2].position = sf::Vector2f((j+1) * Constants::TILE_WIDTH, (i+1) * Constants::TILE_HEIGHT);
            currentQuad[3].position = sf::Vector2f(j * Constants::TILE_WIDTH, (i+1) * Constants::TILE_HEIGHT);

            currentQuad[0].texCoords = sf::Vector2f(Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + textureCoordinateX * (Constants::TILE_WIDTH + Constants::MAP_TILESET_GRAPHICS_OFFSET),
                                                    Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + textureCoordinateY * (Constants::TILE_HEIGHT + Constants::MAP_TILESET_GRAPHICS_OFFSET));

            currentQuad[1].texCoords = sf::Vector2f(Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + (textureCoordinateX + 1) * Constants::TILE_WIDTH + textureCoordinateX * Constants::MAP_TILESET_GRAPHICS_OFFSET,
                                                    Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + textureCoordinateY * (Constants::TILE_HEIGHT + Constants::MAP_TILESET_GRAPHICS_OFFSET));

            currentQuad[2].texCoords = sf::Vector2f(Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + (textureCoordinateX + 1) * Constants::TILE_WIDTH + textureCoordinateX * Constants::MAP_TILESET_GRAPHICS_OFFSET,
                                                    Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + (textureCoordinateY + 1) * Constants::TILE_HEIGHT + textureCoordinateY * Constants::MAP_TILESET_GRAPHICS_OFFSET);

            currentQuad[3].texCoords = sf::Vector2f(Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + textureCoordinateX * (Constants::TILE_WIDTH + Constants::MAP_TILESET_GRAPHICS_OFFSET),
                                                    Constants::MAP_TILESET_GRAPHICS_INITIAL_POSITION + (textureCoordinateY + 1) * Constants::TILE_HEIGHT + textureCoordinateY * Constants::MAP_TILESET_GRAPHICS_OFFSET);
        }
    }
}

Map::~Map()
{
    delete [] mapTable;
}

// private methods

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &mapTileset;
    target.draw(mapVertices, states);
}

void Map::fillMapTableOneValue(Tile value)
{
    for(int i = 0; i < widthTilesNumber * heightTilesNumber; ++i)
    {
        mapTable[i] = value;
    }
}

void Map::createMountain(int positionX, int positionY, int width, int height, Tile value)
{
    for(int i = positionY; i < positionY + height; ++i)
    {
        for(int j = positionX; j < positionX + width; ++j)
        {
            mapTable[i * widthTilesNumber + j] = value;
        }
    }
}

void Map::generateMap()
{
    fillMapTableOneValue(Tile(TileType::sand0, "piasek_0"));
    createMountain(0, 0, 5, 3, Tile(TileType::grass1, "trawa_1"));
    createMountain(30, 50, 20, 2, Tile(TileType::ground1, "ziemia_1"));
    createMountain(17, 0, 4, 70, Tile(TileType::water0, "woda_0", false));
    createMountain(45, 5, 26, 20, Tile(TileType::grass0, "trawa_0"));
}

bool Map::isWalkable(int tileIndex)
{
    return mapTable[tileIndex].isWalkable();
}
