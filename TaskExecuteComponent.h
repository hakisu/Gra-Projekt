#ifndef TASK_EXECUTE_COMPONENT_H
#define TASK_EXECUTE_COMPONENT_H

#include <memory>

#include "Component.h"
#include "Task.h"

class TaskExecuteComponent : public Component
{
public:
    TaskExecuteComponent();
    TaskExecuteComponent(const TaskExecuteComponent &taskExecuteComponent);
    TaskExecuteComponent* clone() const override;

    Task* getCurrentTask();
    void setCurrentTask(Task *task = nullptr);

    void acceptMessage(MessageType messageType);
    virtual void update(GameEntity& gameEntity);

private:
    std::unique_ptr<Task> currentTask;
};

#endif // TASK_EXECUTE_COMPONENT_H
