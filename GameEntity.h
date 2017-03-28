#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <vector>
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
    GraphicsComponent *graphicsComponent;
//    std::vector<Component*> components;
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
    void update();

    // temp
    std::vector<Component*> components;
};

#endif // GAME_ENTITY_H
