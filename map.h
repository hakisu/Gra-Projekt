#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"

class Tile;

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

    // nowe metody
    void mountainGenerator();
    void lakeGenerator(int posX, int posY, int width, int height);
    void riverGenerator(int currentX, int currentY, int toX, int toY);
    // wywolywany wewnetrznie prez lakeGenerator(), nie uzywac metody jako samej
    void sandFillerGenerator(int posX, int posY, int width, int height);

public:
    Map(int widthTilesNumber, int heightTilesNumber);
    ~Map();

    bool isWalkable(int tileIndex);
};

#endif // MAP_H
