#include "GameEntity.h"
#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent()
{
    texture.loadFromFile("Graphics/Characters/temp.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

void GraphicsComponent::render(GameEntity& gameEntity, sf::RenderWindow& window)
{
    sprite.setPosition(gameEntity.posX, gameEntity.posY);
    window.draw(sprite);
}

