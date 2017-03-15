#include <SFML/Graphics.hpp>
#include "InputManager.h"

#include <iostream>
#include "Game.h"

InputManager::InputManager(sf::RenderWindow& window, sf::View& gameCamera) : window(window), gameCamera(gameCamera)
{

}

void InputManager::handleInput(Game& game)
{
    double moveValue = 10;
    sf::Event event;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        gameCamera.move(-moveValue, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        gameCamera.move(moveValue, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        gameCamera.move(0, -moveValue);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        gameCamera.move(0, moveValue);
    }
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Resized)
        {
            std::cout<< "Nowa szerokosc: " << event.size.width << std::endl;
            std::cout<< "Nowa wysokosc: " << event.size.height << std::endl;
        }
        if(event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }
        if(event.type == sf::Event::MouseWheelScrolled)
        {
            gameCamera.zoom(1 + (-event.mouseWheelScroll.delta) * 0.1);
            gameCamera.setSize(std::floor(gameCamera.getSize().x), std::floor(gameCamera.getSize().y));

//            if(event.mouseWheelScroll.delta > 0)
//                gameCamera.setSize(gameCamera.getSize().x-64, gameCamera.getSize().y-64);
//            else
//                gameCamera.setSize(gameCamera.getSize().x+64, gameCamera.getSize().y+64);
        }
        if(event.type == sf::Event::KeyReleased)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Escape :
                {
                    window.close();
                    return;
                }
                case sf::Keyboard::Space :
                {
                    game.testPause = !game.testPause;
                }
                default :
                {

                }
            }
        }
    }
}
