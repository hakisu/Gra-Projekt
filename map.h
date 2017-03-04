#ifndef MAP_H
#define MAP_H

#include "tile.h"

class Map
{
private:
    // data members
    Tile **mapTable;
    int widthTilesNumber, heightTilesNumber;

    // methods
    /** Wypelniamy cala mapTable jednym rodzajem kafelka */
    void fillMapTableOneValue(Tile value);
    void createMountain(int positionX, int positionY, int width, int height);
public:
    /** Tworzymy mape o szerokosci rownej liczbie widthTilesNumber kafelkow i wysokosci rownej liczbie heightTilesNumber kafelkow */
    Map(int widthTilesNumber, int heightTilesSize);
    /** Zwalniamy pamiec dynamiczna zajmowana przez mapTable */
    ~Map();
};

#endif // MAP_H
