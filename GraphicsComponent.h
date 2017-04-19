#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "SFML/Graphics.hpp"
#include "Component.h"

class GameEntity;

class GraphicsComponent : public Component
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    GraphicsComponent();
    GraphicsComponent* clone() const override;

    void acceptMessage(MessageType messageType);
    void render(GameEntity& gameEntity, sf::RenderWindow& window, double timeProgressValue);
};

#endif // GRAPHICS_COMPONENT_H
