#ifndef COMPONENT_H
#define COMPONENT_H

class GameEntity;

enum class MessageType { destinationReached };

class Component
{
public:
    virtual ~Component() {}
    virtual Component* clone() const = 0;

    virtual void acceptMessage(MessageType messageType) = 0;
    virtual void update(GameEntity& gameEntity) {};
};

#endif // COMPONENT_H
