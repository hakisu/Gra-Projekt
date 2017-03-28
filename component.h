#ifndef COMPONENT_H
#define COMPONENT_H

class GameEntity;

class Component
{
private:
public:
    virtual ~Component() {}
//    virtual void acceptMessage(int i) = 0;
    virtual void update(GameEntity& gameEntity){};
};

#endif // COMPONENT_H
