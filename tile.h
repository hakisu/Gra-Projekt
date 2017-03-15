#ifndef TILE_H
#define TILE_H

#include <string>

using std::string;

class Tile
{
private:
    string tileType;
    bool isWalkable;
    int type;
public:
    Tile();
    Tile(int type, string name);
    ~Tile();
    int getType();
};

#endif // TILE_H
