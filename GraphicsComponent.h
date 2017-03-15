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
    void render(GameEntity& gameEntity, sf::RenderWindow& window);
};

#endif // GRAPHICS_COMPONENT_H