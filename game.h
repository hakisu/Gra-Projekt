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
    GameEntity* hero1;
    GameEntity* hero2;
    std::vector<GameEntity> objects;

public:
    Game(sf::RenderWindow& window);
    void render(double timeProgressValue);
    int run();
    void update();
    bool testPause = false;
};


#endif // GAME_H