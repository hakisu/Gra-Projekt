#include "GameEntity.h"
#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent()
{
    texture.loadFromFile("Graphics/Characters/temp.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

void GraphicsComponent::render(GameEntity& gameEntity, sf::RenderWindow& window, double timeProgressValue)
{
    sprite.setPosition(gameEntity.posX, gameEntity.posY);
    // timeProgressValue uzyte w states do interpolacji / ekstrapolacji pozycji do wyswietlenia miedzy updatami silnika gry
    sf::RenderStates states;
    states.transform.translate(gameEntity.changePosX * timeProgressValue, gameEntity.changePosY * timeProgressValue);
    window.draw(sprite, states);
}

