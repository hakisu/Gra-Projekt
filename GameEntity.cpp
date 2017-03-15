#include "GameEntity.h"

GameEntity::GameEntity(double posX, double posY, GraphicsComponent* graphics)
{
    this->posX = posX;
    this->posY = posY;
    graphicsComponent = graphics;
}

void GameEntity::addComponent(Component* newComponent)
{
    components.push_back(newComponent);
}

void GameEntity::render(sf::RenderWindow& window)
{
    graphicsComponent->render(*this, window);
}

void GameEntity::update()
{
    for(auto it = components.begin(); it != components.end(); ++it)
    {
        (*it)->update(*this);
    }
}
