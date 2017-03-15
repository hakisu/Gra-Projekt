#include "tile.h"

Tile::Tile()
{
    tileType = "default";
    type = 0;
    isWalkable = true;
}

Tile::Tile(int type, string name)
{
    this->type = type;
    tileType = name;
    isWalkable = true;
}

Tile::~Tile()
{

}

int Tile::getType()
{
    return type;
}
