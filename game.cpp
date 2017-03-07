#include <chrono>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Map.h"
#include <iostream>

using namespace std::chrono;
using namespace std;

const int GAME_SPEED = 10;

Game::Game(sf::RenderWindow& window) : window(window), inputManager(window, view)
{

}

int Game::run()
{
    Map mapa(300,300);

    view.reset(sf::FloatRect(0, 0, 400, 400));

    sf::CircleShape shape(50);
    shape.setPosition(1200, 0);






    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return 0;
    sf::Text text;
    text.setFont(font);
    text.setString("hello world");
    text.setCharacterSize(44);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Underlined | sf::Text::Bold);


    sf::VertexArray testArray(sf::Triangles, 3);
    testArray[0].position = sf::Vector2f(0, 0);
    testArray[1].position = sf::Vector2f(100, 0);
    testArray[2].position = sf::Vector2f(0, 100);
    testArray[0].color = sf::Color::Blue;
    testArray[1].color = sf::Color::Red;
    testArray[2].color = sf::Color::Green;


    double timeDelay = 0;
    auto previousTimeMeasure = high_resolution_clock::now();
    while(window.isOpen())
    {
        auto newTimeMeasure = high_resolution_clock::now();
        double timeDifference = duration_cast<milliseconds>(newTimeMeasure - previousTimeMeasure).count();
        timeDelay += timeDifference;
        previousTimeMeasure = newTimeMeasure;

        // Obsluga inputu
        inputManager.handleInput();



        while(timeDelay >= GAME_SPEED)
        {
            // silnik ai,physics...
            timeDelay -= GAME_SPEED;
        }

        window.setView(view);
        window.clear(sf::Color::Black);
//        window.draw(text);
        window.draw(testArray);
        window.draw(shape);
        window.display();
    }
    return 0;
}

//        std::this_thread::sleep_for(milliseconds(20));
