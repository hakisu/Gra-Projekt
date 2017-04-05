#include "Tile.h"

Tile::Tile()
{
    type = TileType::ground0;
    walkable = true;
}

Tile::Tile(TileType type, string name, bool walkable, int areaNumber)
{
    this->type = type;
    this->tileName = name;
    this->walkable = walkable;
    this->areaNumber = areaNumber;
}

Tile::~Tile()
{

}

TileType Tile::getType()
{
    return type;
}

bool Tile::isWalkable()
{
    return walkable;
}


int Tile::getAreaNumber()
{
    return this->areaNumber;
}

void Tile::setAreaNumber(int areaNumber)
{
    this->areaNumber = areaNumber;
}
