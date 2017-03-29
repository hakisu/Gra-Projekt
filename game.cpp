#include "Game.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <typeinfo>

#include "Constants.h"
#include "GameLibrary.h"
#include "GraphicsComponent.h"
#include "Map.h"
#include "MovementComponent.h"
#include "PathDisplaySystem.h"
#include "RandomNumberGenerator.h"

using namespace std::chrono;
using namespace std;

Game::Game(sf::RenderWindow& window) : window(window), inputManager(window, gameCamera),
                                       gameMap(Constants::MAP_WIDTH, Constants::MAP_HEIGHT),
                                       currentGameSpeed(Constants::GAME_SPEED)
{
    this->numberOfObjects = Constants::INITIAL_OBJECTS_RESERVED;
    objects.reserve(Constants::INITIAL_OBJECTS_RESERVED);

    for(int i = 0; i < numberOfObjects; ++i)
    {
        objects.emplace_back(RandomNumberGenerator::getIntNumber(0, Constants::MAP_WIDTH - 1),
                             RandomNumberGenerator::getIntNumber(0, Constants::MAP_HEIGHT - 1),
                             new GraphicsComponent());
        objects[i].addComponent(new MovementComponent(gameMap));
    }
    cout << "\n\n Zaczynamy run() :\n\n";
}

int Game::run()
{
    ofstream fileHandle;
    fileHandle.open("time_logs.txt");
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

        while(timeDelay >= currentGameSpeed)
        {
            // silnik ai,physics...
            if(testPause == false)
                update();
            timeDelay -= currentGameSpeed;
        }

        // Renderowanie grafiki
        render(timeDelay / currentGameSpeed);

        if(timeDifference > 10)
            fileHandle << timeDifference << "\n";
    }
    fileHandle.close();
    return 0;
}

void Game::render(double timeProgressValue)
{
    window.setView(gameCamera);

    window.clear(sf::Color::Black);

    window.draw(gameMap);

    if(testPause == true)
        timeProgressValue = 0;

    for(auto &i : objects)
    {
        i.render(window, timeProgressValue);
        if(displayPath)
            PathDisplaySystem::render(i, window);
    }

    window.display();
}

void Game::update()
{
    for(int i = 0; i < numberOfObjects; ++i)
        objects[i].update();
//    thread first(&Game::foo, this, 0, numberOfObjects/2);
//    thread second(&Game::foo, this, numberOfObjects/2, numberOfObjects);
//    first.join();
//    second.join();
}

void Game::foo(int start, int end)
{
    for(int i = start; i < end; ++i)
        objects[i].update();
}

void Game::setGameSpeed(unsigned newGameSpeed)
{
    this->currentGameSpeed = newGameSpeed;
}

Map& Game::getMap()
{
    return this->gameMap;
}
