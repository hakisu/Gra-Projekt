#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

class Game;

class InputManager
{
private:
    sf::RenderWindow& window;
    sf::View& gameCamera;
public:
    InputManager(sf::RenderWindow& window, sf::View& gameCamera);
    void handleInput(Game& game);
};

#endif // INPUT_MANAGER_H
