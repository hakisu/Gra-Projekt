#include "GameEntity.h"
#include "GraphicsComponent.h"

#include <iostream>

GraphicsComponent::GraphicsComponent()
{
    texture.loadFromFile("Graphics/Characters/temp.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

void GraphicsComponent::render(GameEntity& gameEntity, sf::RenderWindow& window, double timeProgressValue)
{
    sprite.setPosition(gameEntity.getPosX(), gameEntity.getPosY());

    // timeProgressValue uzyte w states do interpolacji / ekstrapolacji pozycji do wyswietlenia miedzy updatami silnika gry
    sf::RenderStates states;
    states.transform.translate(gameEntity.getCurrentChangeInPosX() * timeProgressValue, gameEntity.getCurrentChangeInPosY() * timeProgressValue);

    window.draw(sprite, states);
}
