#ifndef TILE_H
#define TILE_H

#include <string>

using std::string;

enum class TileType { grass0, grass1, ground0, ground1, sand0, water0 = 6, rock0 = 7 };

class Tile
{
private:
    string tileName;
    bool walkable;
    TileType type;
    int areaNumber;

public:
    Tile();
    Tile(TileType type, string name, bool walkable = true, int areaNumber = 0);
    ~Tile();

    TileType getType();
    bool isWalkable();
    int getAreaNumber();
    void setAreaNumber(int areaNumber);
};

#endif // TILE_H
