#ifndef GAME_H
#define GAME_H

#include "InputManager.h"
#include "Map.h"
#include "GameEntity.h"

class Game
{
private:
    sf::RenderWindow& window;
    InputManager inputManager;
    Map gameMap;
    sf::View gameCamera;
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
