#include <iostream>
#include <thread>

#include "Component.h"
#include "Game.h"
#include "Map.h"

using namespace std;

int main()
{
    while(true)
    {
        try
        {
            sf::ContextSettings settings;
            // Nie uzywamy antyaliasingu, gdyz nawet mala wartosc powyzej 0 powoduje powstawanie lini(artefaktow) miedzy plytkami planszy, kiedy uzywany jest zoom
            settings.antialiasingLevel = 0;
            sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Tytul okna", sf::Style::Close, settings);

            Game *game = new Game(window);
            game->run();
            delete game;
        }
        catch(std::exception &e)
        {
            cout << e.what() << endl;
        }

        cout << "Wpisz 0 aby wylaczyc gre, inna cyfre aby stworzyc nowa gre: \n";
        int a;
        cin >> a;
        if(a == 0)
            break;
    }

    return 0;
}
