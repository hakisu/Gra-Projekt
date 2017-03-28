#ifndef TILE_H
#define TILE_H

#include <string>

using std::string;

enum class TileType { grass0, grass1, ground0, ground1, sand0, water0 = 6 };

class Tile
{
private:
    string tileName;
    bool walkable;
    TileType type;
public:
    Tile();
    Tile(TileType type, string name, bool walkable = true);
    ~Tile();
    TileType getType();
    bool isWalkable();
};

#endif // TILE_H
