#ifndef TILE_H
#define TILE_H

#include <string>

using std::string;

class Tile
{
private:
    string tileType;
public:
    Tile();
    Tile(string name);
    ~Tile();

};

#endif // TILE_H
