#ifndef GAME_LIBRARY_H
#define GAME_LIBRARY_H

#include "GraphicsComponent.h"
#include "GameEntity.h"

#include <iostream>
using namespace std;
namespace gl
{
    // factory functions
    GameEntity createCharacter();

    // helpful functions
    int calculateTileIndex(int positionX, int positionY);
    int calculateHeuristicDistance(int startTileIndex, int endTileIndex);
    void changePositionToWorldPosition(int &mouseX, int &mouseY, sf::RenderWindow &window);

    // template functions
    template<typename T>
    T* getComponentPtr(GameEntity &gameEntity)
    {
        for(auto &componentReference : gameEntity.components)
        {
            if(typeid(T) == typeid(*componentReference))
            {
                return static_cast<T*>(componentReference.get());
            }
        }
        return nullptr;
    }
}

#endif // GAME_LIBRARY_H
