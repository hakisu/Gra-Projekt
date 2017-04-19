#ifndef GAME_H
#define GAME_H

#include "ContextMenuOrders.h"
#include "GameClock.h"
#include "GameEntity.h"
#include "InputManager.h"
#include "Map.h"
#include "TaskExecuteSystem.h"

using sf::RenderWindow;
using sf::View;

class Game
{
//private:
public:
    RenderWindow& window;
    InputManager inputManager;
    Map gameMap;
    View gameCamera;
    GameClock gameClock;
    ContextMenuOrders contextMenuOrders;
    TaskExecuteSystem taskExecuteSystem;

    unsigned int currentGameSpeed;

public:
    Game(sf::RenderWindow& window);

    void setGameSpeed(unsigned newGameSpeed);
    Map& getMap();

    void render(double timeProgressValue);
    int run();
    void update();

    // tymczasowe, do testow
    bool testPause = true;
    bool displayPath = false;
    int numberOfObjects;
    std::vector<GameEntity> objects;
    void foo(int start, int end);
};

#endif // GAME_H
