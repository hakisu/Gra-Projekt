#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <memory>
#include <vector>

#include "Component.h"

class Component;
class GraphicsComponent;
namespace sf
{
    class RenderWindow;
}

class GameEntity
{
private:
    float posX;
    float posY;
    float currentChangeInPosX;
    float currentChangeInPosY;
    std::unique_ptr<GraphicsComponent> graphicsComponent;
    static int entitesNumber;

public:
    GameEntity(unsigned int posXIndex, unsigned int posYIndex, GraphicsComponent* graphics);
    GameEntity(const GameEntity& gameEntity);
    ~GameEntity();

    float getCurrentChangeInPosX() const;
    float getCurrentChangeInPosY() const;
    float getPosX() const;
    float getPosY() const;
    void setCurrentChangeInPosX(float currentChangeInPosX);
    void setCurrentChangeInPosY(float currentChangeInPosY);
    void setPosX(float posX);
    void setPosY(float posY);

    void addComponent(Component* newComponent);
    void render(sf::RenderWindow& window, double timeProgressValue);
    void sendMessage(MessageType messageType);
    void update();

    // temp
    std::vector<std::unique_ptr<Component>> components;
};

#endif // GAME_ENTITY_H
