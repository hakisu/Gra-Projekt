#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <vector>
#include "Component.h"
#include "GraphicsComponent.h"

class Game;

class GameEntity
{
private:
    std::vector<Component*> components;
    GraphicsComponent *graphicsComponent;
public:
    GameEntity(double posX, double posY, GraphicsComponent* graphics);
    void addComponent(Component* newComponent);
    void render(sf::RenderWindow& window);
    void update();

    // zrobic gettery i settery do tego, przestawic na private
    double posX;
    double posY;
};
#endif // GAME_ENTITY_H
