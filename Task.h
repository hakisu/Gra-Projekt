#ifndef TASK_H
#define TASK_H

#include "Component.h"

class GameEntity;

class Task
{
    friend class TaskExecuteSystem;

public:
    Task(int tileIndex);
    virtual ~Task() {};
    virtual Task* clone() const = 0;

    virtual void acceptTaskMessage(MessageType messageType) = 0;
    virtual void update(GameEntity & gameEntity) = 0;

protected:
    int tileIndex;
};

class TaskCutTree : public Task
{
public:
    TaskCutTree(int tileIndex);
    TaskCutTree* clone() const override { return new TaskCutTree(*this); }

    void acceptTaskMessage(MessageType messageType) override;
    void update(GameEntity & gameEntity);

private:
    bool pathSet = false;
    bool destinationReached = false;
    bool taskBeingPerformed = false;
    bool taskFinished = false;
};

#endif // TASK_H
