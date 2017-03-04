#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
private:
public:
    virtual ~Component() = 0;
    virtual void acceptMessage(int i) = 0;
};

#endif // COMPONENT_H
