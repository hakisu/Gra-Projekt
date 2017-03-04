#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "map.h"
#include "component.h"

using namespace std::chrono;
const int GAME_SPEED = 10;

class A
{
private:
    int a;
public:
    virtual void receive() = 0;
};

class B : public A
{
    void receive()
    {
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Udalo sie!");
    Map mapa(300,300);

    B b;
    std::cout << sizeof(b) << std::endl;


    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return 0;
    sf::Text text;
    text.setFont(font);
    text.setString("hello world");
    text.setCharacterSize(44);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Underlined | sf::Text::Bold);

    double timeDelay = 0;
    auto previousTimeMeasure = high_resolution_clock::now();
    while(true)
    {
        auto newTimeMeasure = high_resolution_clock::now();
        double timeDifference = duration_cast<milliseconds>(newTimeMeasure - previousTimeMeasure).count();
        timeDelay += timeDifference;
        previousTimeMeasure = newTimeMeasure;

        // Obsluga inputu
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            if(event.type == sf::Event::KeyPressed)
            {
                window.close();
                return 0;
            }
        }
//        std::this_thread::sleep_for(milliseconds(20));

        while(timeDelay >= GAME_SPEED)
        {
            // silnik ai,physics...
            timeDelay -= GAME_SPEED;
        }


        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}
