#include "PathDisplaySystem.h"

#include <iostream>
#include <typeinfo>

#include "Constants.h"
#include "GameEntity.h"
#include "MovementComponent.h"
#include "RandomNumberGenerator.h"

using namespace std;
void PathDisplaySystem::render(GameEntity& gameEntity, sf::RenderWindow& window)
{
    bool displayPath = false;
    MovementComponent *movementComponentPtr = nullptr;

    for(auto &i : gameEntity.components)
    {
        if(typeid(*i) == typeid(MovementComponent))
        {
            displayPath = true;
            movementComponentPtr = static_cast<MovementComponent*>(i.get());
            break;
        }
    }

    if(displayPath)
    {
        const vector<int> &currentPath = movementComponentPtr->getPath();

        // do poprawienia, aby kolor byl staly dla sciezki po wylosowaniu
//        sf::Color pathColor(RandomNumberGenerator::getIntNumber(0, 255), RandomNumberGenerator::getIntNumber(0, 255), RandomNumberGenerator::getIntNumber(0, 255));
        sf::Color pathColor(sf::Color::Red);
        for(auto &i : currentPath)
        {
            int posX = (i % Constants::MAP_WIDTH) * Constants::TILE_WIDTH;
            int posY = (i / Constants::MAP_WIDTH) * Constants::TILE_HEIGHT;

            sf::RectangleShape currentTileMarker(sf::Vector2f(Constants::TILE_WIDTH, Constants::TILE_HEIGHT));
            currentTileMarker.setPosition(posX, posY);
            currentTileMarker.setOutlineColor(pathColor);
            currentTileMarker.setOutlineThickness(-5);
            currentTileMarker.setFillColor(sf::Color::Transparent);

            window.draw(currentTileMarker);
        }
    }
}
