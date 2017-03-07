#ifndef GAME_H
#define GAME_H

#include "InputManager.h"

class Game
{
private:
    sf::RenderWindow& window;
    InputManager inputManager;

public:
    Game(sf::RenderWindow& window);
    int run();
    sf::View view;
};


#endif // GAME_H
