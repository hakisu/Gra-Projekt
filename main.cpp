#include <iostream>
#include <thread>
#include "Game.h"
#include "Map.h"
#include "Component.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Tytul okna", sf::Style::Default, settings);
    Game game(window);
    game.run();

    return 0;
}
