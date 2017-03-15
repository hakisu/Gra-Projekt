#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"
#include "tile.h"

enum class TileType;

class Map : public sf::Drawable, public sf::Transformable
{
private:
    // data members
    Tile *mapTable;
    int widthTilesNumber, heightTilesNumber;
    sf::Texture mapTileset;
    sf::VertexArray mapVertices;

    // methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void fillMapTableOneValue(Tile value);
    void createMountain(int positionX, int positionY, int width, int height, Tile value);
    void generateMap();

public:
    Map(int widthTilesNumber, int heightTilesNumber);
    ~Map();
};

enum class TileType{grass, ground, sand, water};
#endif // MAP_H
