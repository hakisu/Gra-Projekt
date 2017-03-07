#include "map.h"

// public methods
Map::Map(int widthTilesNumber, int heightTilesNumber)
{
    mapTable = new Tile*[widthTilesNumber];
    for(int i = 0; i < widthTilesNumber; ++i)
        mapTable[i] = new Tile[heightTilesNumber];

    this->widthTilesNumber = widthTilesNumber;
    this->heightTilesNumber = heightTilesNumber;
}

Map::~Map()
{
    for(int i = 0; i < widthTilesNumber; ++i)
        delete [] mapTable[i];
    delete [] mapTable;
}

// private methods

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
void Map::fillMapTableOneValue(Tile value)
{
    for(int i = 0; i < widthTilesNumber; ++i)
    {
        for(int j = 0; j < heightTilesNumber; ++j)
        {
            mapTable[i][j] = value;
        }
    }
}

void Map::createMountain(int positionX, int positionY, int width, int height)
{

}
