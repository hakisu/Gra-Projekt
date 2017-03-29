#include "map.h"

#include <iostream>

#include "Constants.h"
#include "RandomNumberGenerator.h"
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
    fillMapTableOneValue(Tile(TileType::grass1, "trawa_1"));
//    createMountain(0, 0, 5, 3, Tile(TileType::grass1, "trawa_1"));
//    createMountain(30, 50, 20, 2, Tile(TileType::ground1, "ziemia_1"));
//    createMountain(17, 0, 4, 70, Tile(TileType::water0, "woda_0", false));
//    createMountain(45, 5, 26, 20, Tile(TileType::grass0, "trawa_0"));
    mountainGenerator();
    std::cout << "Skaly zrobione!\n";
    lakeGenerator(30, 10, 30, 30);
    std::cout << "Jezioro zrobione!\n";
    riverGenerator(0, 50, RandomNumberGenerator::getIntNumber(Constants::MAP_WIDTH / 2 , Constants::MAP_WIDTH - 1), RandomNumberGenerator::getIntNumber(5, Constants::MAP_HEIGHT - 10));


    sandGenerator();
    std::cout<< "Piasek zrobiony!\n";




}

bool Map::isWalkable(int tileIndex)
{
    return mapTable[tileIndex].isWalkable();
}

void Map::mountainGenerator()
{
    // generowanie skalek

    int randomNumber = 0;

    for(int y = 1; y < heightTilesNumber - 1; ++y)
    {
        for(int x = 1; x < widthTilesNumber - 1; ++x)
        {
            randomNumber = RandomNumberGenerator::getIntNumber(0, 8);
            if(randomNumber == 3 || randomNumber == 4)
            {
                mapTable[y * widthTilesNumber + x] = Tile(TileType::rock0, "skala_0", false);
            }
        }
    }

    // usuwanie pojedynczych skalek
    for(int y = 1; y < heightTilesNumber - 1; ++y)
    {
        for(int x = 1; x < widthTilesNumber - 1; ++x)
        {
            if(mapTable[y * widthTilesNumber + x].getType() == TileType::rock0)
            {
                if((mapTable[y * widthTilesNumber + x - 1].getType() != TileType::rock0) &&
                   (mapTable[y * widthTilesNumber + x + 1].getType() != TileType::rock0) &&
                   (mapTable[(y-1) * widthTilesNumber + x].getType() != TileType::rock0) &&
                   (mapTable[(y+1) * widthTilesNumber + x].getType() != TileType::rock0) &&
                   (mapTable[(y-1) * widthTilesNumber + x - 1].getType() != TileType::rock0) &&
                   (mapTable[(y+1) * widthTilesNumber + x + 1].getType() != TileType::rock0) &&
                   (mapTable[(y-1) * widthTilesNumber + x + 1].getType() != TileType::rock0) &&
                   (mapTable[(y+1) * widthTilesNumber + x - 1].getType() != TileType::rock0))
                {
                    mapTable[y * widthTilesNumber + x] = Tile(TileType::grass0, "trawa_0");
                }
            }
        }
    }
}

void Map::lakeGenerator(int posX, int posY, int width, int height)
{
    // generowanie jeziora
    for(int y = posY; y < height + posY - 1; ++y)
    {
        int number1 = RandomNumberGenerator::getIntNumber(0, 9) + 3;
        int number2 = RandomNumberGenerator::getIntNumber(0, 9) + 3;

        int left = RandomNumberGenerator::getIntNumber(0, width / number1);
        int right = RandomNumberGenerator::getIntNumber(0, width / number2);
        if(y < posY + 4 || y > height - 4)
        {
            left = RandomNumberGenerator::getIntNumber(0, width / 2 - 1);
            right = RandomNumberGenerator::getIntNumber(0, width / 2 - 1);
        }

        for(int x = posX + left + 1; x < width + posX - right - 1; ++x)
        {
            mapTable[y * widthTilesNumber + x] = Tile(TileType::water0, "woda_0", false);
        }
    }

    // lake modifier

    for(int y = posY; y < height + posY; ++y)
    {
        for(int x = posX; x < width + posX; ++x)
        {
            if(mapTable[y * widthTilesNumber + x].getType() == TileType::water0)
            {
                if(mapTable[(y + 1) * widthTilesNumber + x].getType() != TileType::water0 &&
                   mapTable[(y - 1) * widthTilesNumber + x].getType() != TileType::water0)
                {
                    mapTable[y * widthTilesNumber + x] = Tile(TileType::grass1, "trawa_1");
                }
            }
            if(mapTable[y * widthTilesNumber + x].getType() != TileType::water0)
            {
                if(mapTable[(y + 1) * widthTilesNumber + x].getType() == TileType::water0 &&
                   mapTable[(y-1) * widthTilesNumber + x ].getType() == TileType::water0)
                {
                    mapTable[y * widthTilesNumber + x] = Tile(TileType::water0,"water_0");
                }
            }
        }
    }
}

void Map::sandGenerator()
{
    for(int y = 1; y < heightTilesNumber - 1; ++y)
    {
        for(int x = 1; x < widthTilesNumber - 1; ++x)
        {
            if(mapTable[y * widthTilesNumber + x].getType() == TileType::water0)
            {
                if(mapTable[y * widthTilesNumber + x + 1].getType() != TileType::water0) //1
                {
                    mapTable[y * widthTilesNumber + x + 1] = Tile(TileType::sand0,"sand_0");
                }
                if(mapTable[y * widthTilesNumber + x - 1].getType() != TileType::water0) //2
                {
                    mapTable[y * widthTilesNumber + x - 1] = Tile(TileType::sand0,"sand_0");
                }
                if(mapTable[(y - 1) * widthTilesNumber + x].getType() != TileType::water0) //3
                {
                    mapTable[(y - 1) * widthTilesNumber + x] = Tile(TileType::sand0,"sand_0");
                }
                if(mapTable[(y + 1) * widthTilesNumber + x].getType() != TileType::water0) //4
                {
                    mapTable[(y + 1) * widthTilesNumber + x] = Tile(TileType::sand0,"sand_0"); //4
                }
                if(mapTable[(y + 1) * widthTilesNumber + x + 1].getType() != TileType::water0) //5 now diagonals
                {
                    mapTable[(y + 1) * widthTilesNumber + x + 1] = Tile(TileType::sand0,"sand_0");
                }
                if(mapTable[(y - 1) * widthTilesNumber + x - 1].getType() != TileType::water0) //6
                {
                    mapTable[(y - 1) * widthTilesNumber + x - 1] = Tile(TileType::sand0,"sand_0");
                }
                if(mapTable[(y - 1) * widthTilesNumber + x + 1].getType() != TileType::water0) //7
                {
                    mapTable[(y - 1) * widthTilesNumber + x + 1] = Tile(TileType::sand0,"sand_0");
                }
                if(mapTable[(y + 1) * widthTilesNumber + x - 1].getType() != TileType::water0) //8
                {
                    mapTable[(y + 1) * widthTilesNumber + x - 1] = Tile(TileType::sand0,"sand_0");
                }

            }
        }
    }
}

void Map::riverGenerator(int currentX, int currentY, int toX, int toY)
{
    int randomNumber = 0;
    int number = 5;

    // zmienilem tu tymczasowo AND na OR
    while(currentX != toX || currentY != toY)
    {
        randomNumber = RandomNumberGenerator::getIntNumber(0, number - 1) + 2;

        if(currentX < toX)
        {
           for(int i = 0; i < randomNumber; ++i)
                mapTable[currentY * widthTilesNumber + currentX++] = Tile(TileType::water0, "woda_0", false);
        }
        else
        {
            randomNumber = RandomNumberGenerator::getIntNumber(0, number - 1) + 2;
            for(int i = 0; i < randomNumber; ++i)
                mapTable[currentY * widthTilesNumber + currentX--] = Tile(TileType::water0, "woda_0", false);
        }

        if(currentY < toY)
        {
            randomNumber = RandomNumberGenerator::getIntNumber(0, number - 1) + 2;
            for(int i = 0; i < randomNumber; ++i)
                mapTable[currentY++ * widthTilesNumber + currentX] = Tile(TileType::water0, "woda_0", false);
        }
        else
        {
            randomNumber = RandomNumberGenerator::getIntNumber(0, number - 1) + 2;
            for(int i = 0; i < randomNumber; ++i)
                mapTable[currentY-- * widthTilesNumber + currentX] = Tile(TileType::water0, "woda_0", false);
        }
    }
    std::cout << currentX << std::endl;
    std::cout << toX << std::endl;
    std::cout << currentY << std::endl;
    std::cout << toY << std::endl;
}
