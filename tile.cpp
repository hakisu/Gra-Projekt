#include "tile.h"

Tile::Tile()
{
    type = TileType::ground0;
    walkable = true;
}

Tile::Tile(TileType type, string name, bool walkable)
{
    this->type = type;
    this->tileName = name;
    this->walkable = walkable;
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
