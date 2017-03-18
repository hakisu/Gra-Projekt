#include <chrono>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Map.h"
#include "Constants.h"
#include "PhysicsComponent.h"

using namespace std::chrono;
using namespace std;

Game::Game(sf::RenderWindow& window) : window(window), inputManager(window, gameCamera), gameMap(Constants::MAP_WIDTH, Constants::MAP_HEIGHT)
{
    hero1 = new GameEntity(70, 20, new GraphicsComponent());
    hero2 = new GameEntity(400, 320, new GraphicsComponent());
    hero1->addComponent(new PhysicsComponent());
    hero2->addComponent(new PhysicsComponent());
    for(int i = 0; i < numberOfObjects; ++i)
    {
        objects.push_back(GameEntity(3500, 3500, new GraphicsComponent()));
        objects[i].addComponent(new PhysicsComponent());
    }
}

int Game::run()
{
    gameCamera.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    gameCamera.setCenter(3000, 3000);
    sf::RenderStates states;

    double timeDelay = 0;
    auto previousTimeMeasure = high_resolution_clock::now();
    while(window.isOpen())
    {
        this_thread::sleep_for(1ms);
        // Pomiar czasu wykonywania 1 klatki gry
        auto newTimeMeasure = high_resolution_clock::now();
        double timeDifference = duration_cast<milliseconds>(newTimeMeasure - previousTimeMeasure).count();
        timeDelay += timeDifference;
        previousTimeMeasure = newTimeMeasure;

        // Obsluga inputu
        inputManager.handleInput(*this);

        while(timeDelay >= Constants::GAME_SPEED)
        {
            // silnik ai,physics...
            if(testPause == false)
                update();
            timeDelay -= Constants::GAME_SPEED;
        }

        // Renderowanie grafiki
        render(timeDelay / Constants::GAME_SPEED);
    }
    return 0;
}

void Game::render(double timeProgressValue)
{
    window.setView(gameCamera);

    window.clear(sf::Color::Black);

    window.draw(gameMap);

    if(testPause == true)
        timeProgressValue = 0;

    hero1->render(window, timeProgressValue);
    hero2->render(window, timeProgressValue);
    for(int i = 0; i < numberOfObjects; ++i)
        objects[i].render(window, timeProgressValue);

    window.display();
}

void Game::update()
{
    hero1->update();
    hero2->update();
    for(int i = 0; i < numberOfObjects; ++i)
        objects[i].update();
}
