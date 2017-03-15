#include <iostream>
#include <thread>
#include "Game.h"
#include "Map.h"
#include "Component.h"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    // Nie uzywamy antyaliasingu, gdyz nawet mala wartosc powyzej 0 powoduje powstawanie lini(artefaktow) miedzy plytkami planszy, kiedy uzywany jest zoom
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Tytul okna", sf::Style::Default, settings);

    Game game(window);
    game.run();

    return 0;
}
