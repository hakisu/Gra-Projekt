#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>
class InputManager
{
private:
    sf::RenderWindow& window;
    sf::View& view;
public:
    InputManager(sf::RenderWindow& window, sf::View& view);
    void handleInput();
};

#endif // INPUT_MANAGER_H
