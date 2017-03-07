#include <SFML/Graphics.hpp>
#include "InputManager.h"

#include <iostream>

InputManager::InputManager(sf::RenderWindow& window, sf::View& view) : window(window), view(view)
{

}

void InputManager::handleInput()
{
    double moveValue = 0.05;
    sf::Event event;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        view.move(-moveValue, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        view.move(moveValue, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        view.move(0, -moveValue);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        view.move(0, moveValue);
    }
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }
        if(event.type == sf::Event::MouseWheelScrolled)
        {
            std::cout << event.mouseWheelScroll.delta << std::endl;
            view.zoom(1 + (-event.mouseWheelScroll.delta) * 0.1);
        }
        switch(event.key.code)
        {
            case sf::Keyboard::Escape :
            {
                window.close();
                return;
                }
            default :
            {

            }
        }
    }
}
