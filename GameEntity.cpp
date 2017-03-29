#include "GameEntity.h"

#include <iostream>

#include "Constants.h"
#include "GraphicsComponent.h"

int GameEntity::entitesNumber = 0;

GameEntity::GameEntity(unsigned int posXIndex, unsigned int posYIndex, GraphicsComponent* graphics)
{
    this->posX = posXIndex * Constants::TILE_WIDTH;
    this->posY = posYIndex * Constants::TILE_HEIGHT;
    this->currentChangeInPosX = 0;
    this->currentChangeInPosY = 0;
    graphicsComponent = graphics;
    entitesNumber++;

    std::cout << "Liczba jednostek : " << entitesNumber << " X : " << posXIndex << " Y : " << posYIndex << "\n";
}

GameEntity::GameEntity(const GameEntity& gameEntity)
{
    this->posX = gameEntity.posX;
    this->posY = gameEntity.posY;
    this->currentChangeInPosX = gameEntity.currentChangeInPosX;
    this->currentChangeInPosY = gameEntity.currentChangeInPosY;
    this->graphicsComponent = gameEntity.graphicsComponent;
    this->components = gameEntity.components;
    entitesNumber++;

    std::cout << "Skonczylismy copy constructor." << std::endl;
}

GameEntity::~GameEntity()
{
    entitesNumber--;
    std::cout << "Destruktor wywolany." << std::endl;
}

void GameEntity::addComponent(Component* newComponent)
{
    components.push_back(newComponent);
}

void GameEntity::render(sf::RenderWindow& window, double timeProgressValue)
{
    graphicsComponent->render(*this, window, timeProgressValue);
}

void GameEntity::update()
{
    for(auto it = components.begin(); it != components.end(); ++it)
    {
        (*it)->update(*this);
    }
}

float GameEntity::getCurrentChangeInPosX() const
{
    return currentChangeInPosX;
}

float GameEntity::getCurrentChangeInPosY() const
{
    return currentChangeInPosY;
}

float GameEntity::getPosX() const
{
    return posX;
}

float GameEntity::getPosY() const
{
    return posY;
}

void GameEntity::setCurrentChangeInPosX(float currentChangeInPosX)
{
    this->currentChangeInPosX = currentChangeInPosX;
}

void GameEntity::setCurrentChangeInPosY(float currentChangeInPosY)
{
    this->currentChangeInPosY = currentChangeInPosY;
}

void GameEntity::setPosX(float posX)
{
    this->posX = posX;
}

void GameEntity::setPosY(float posY)
{
    this->posY = posY;
}
