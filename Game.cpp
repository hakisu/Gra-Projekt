#include "Game.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <typeinfo>

#include "Constants.h"
#include "ContextMenuOrders.h"
#include "GameLibrary.h"
#include "GraphicsComponent.h"
#include "Map.h"
#include "MovementComponent.h"
#include "PathDisplaySystem.h"
#include "RandomNumberGenerator.h"
#include "TaskExecuteComponent.h"

using namespace std::chrono;
using namespace std;

sf::Texture test;
sf::Sprite testSprite;

Game::Game(sf::RenderWindow& window) : window(window), inputManager(window, gameCamera),
                                       gameMap(Constants::MAP_WIDTH, Constants::MAP_HEIGHT),
                                       contextMenuOrders(), taskExecuteSystem(),
                                       currentGameSpeed(Constants::GAME_SPEED)
{
    this->numberOfObjects = Constants::INITIAL_OBJECTS_RESERVED;
    objects.reserve(Constants::INITIAL_OBJECTS_RESERVED);

    for(int i = 0; i < numberOfObjects; ++i)
    {
        objects.emplace_back(RandomNumberGenerator::getIntNumber(0, Constants::MAP_WIDTH - 1),
                             RandomNumberGenerator::getIntNumber(0, Constants::MAP_HEIGHT - 1),
                             new GraphicsComponent());

        objects[i].addComponent(new TaskExecuteComponent());
        objects[i].addComponent(new MovementComponent(gameMap));
    }

    cout << "\n\n Zaczynamy run() :\n\n";


    test.loadFromFile("Graphics/test.png");
    testSprite.setTexture(test);
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
        // Pomiar czasu wykonywania 1 klatki gry
        auto newTimeMeasure = high_resolution_clock::now();
        double timeDifference = duration_cast<microseconds>(newTimeMeasure - previousTimeMeasure).count();

        // dzielimy przez 1000 bo chcemy miec timeDelay w milisekunach, a timeDifference jest mierzone w mikrosekundach
        timeDelay += timeDifference / 1000;
        previousTimeMeasure = newTimeMeasure;

        while(timeDelay >= currentGameSpeed)
        {
            // Obsluga inputu
            inputManager.handleInput(*this);

            // silnik ai,physics...
            if(testPause == false)
            {
                update();

                gameClock.updateWithOneGameTick();
//                cout << gameClock.getFullDate() << endl;
            }
            timeDelay -= currentGameSpeed;
        }

        // Renderowanie grafiki
        render(timeDelay / currentGameSpeed);

        if(timeDifference / 1000 > 10)
            fileHandle << timeDifference / 1000 << "\n";
    }
    fileHandle.close();
    return 0;
}

void Game::render(double timeProgressValue)
{
    window.setView(gameCamera);

    window.clear(sf::Color::Red);

    window.setView(window.getDefaultView());
    window.draw(testSprite);
    
    window.setView(gameCamera);

    window.draw(gameMap);

    if(testPause == true)
        timeProgressValue = 0;

    for(auto &i : objects)
    {
        i.render(window, timeProgressValue);
        if(displayPath)
            PathDisplaySystem::render(i, window);
    }

    //dzien i noc oswietlenie
//    sf::RectangleShape a;
//
//    a.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
//    a.setPosition(0, 0);
//    a.setFillColor(sf::Color(0, 0, 0, (255.0 / 59) * gameClock.getMinute()));
//
    // Rysowanie elementow niezaleznie od kamery
    window.setView(window.getDefaultView());
//    window.draw(a);

    // rysowanie menu wydawania rozkazow
    window.draw(contextMenuOrders);

    window.setView(gameCamera);
    window.display();
}

void Game::update()
{
    taskExecuteSystem.update(objects, gameMap);

    for(unsigned int i = 0; i < objects.size(); ++i)
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
