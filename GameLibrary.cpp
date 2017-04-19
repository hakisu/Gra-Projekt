#include "GameLibrary.h"

#include "Constants.h"

#include <iostream>
using namespace std;

namespace gl
{
    GameEntity createCharacter()
    {
        GameEntity a(0, 0, new GraphicsComponent());
        return a;
    }

    int calculateTileIndex(int positionX, int positionY)
    {
        int indexX = positionX / Constants::TILE_WIDTH;
        int indexY = positionY / Constants::TILE_HEIGHT;

        int index = indexX + indexY * Constants::MAP_WIDTH;

        return index;
    }

    int calculateHeuristicDistance(int startTileIndex, int endTileIndex)
    {
        int startPosX = startTileIndex % Constants::MAP_WIDTH;
        int startPosY = startTileIndex / Constants::MAP_HEIGHT;
        int endPosX = endTileIndex % Constants::MAP_WIDTH;
        int endPosY = endTileIndex / Constants::MAP_WIDTH;

        return std::abs(endPosX - startPosX) + std::abs(endPosY - startPosY);
    }

    void changePositionToWorldPosition(int &mouseX, int &mouseY, sf::RenderWindow &window)
    {
        sf::Vector2i pixelPos(mouseX, mouseY);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        mouseX = worldPos.x;
        mouseY = worldPos.y;
    }

}
