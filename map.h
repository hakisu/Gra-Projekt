#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"
#include "tile.h"
#include "MapLoader.h"

class Map : public sf::Drawable, public sf::Transformable
{
private:
    // data members
    Tile **mapTable;
    int widthTilesNumber, heightTilesNumber;
    MapLoader loader;

    // methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void fillMapTableOneValue(Tile value);
    void createMountain(int positionX, int positionY, int width, int height);

public:
    Map(int widthTilesNumber, int heightTilesSize);
    ~Map();
};

#endif // MAP_H
