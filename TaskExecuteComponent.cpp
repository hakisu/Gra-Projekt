#include "TaskExecuteComponent.h"

#include "GameEntity.h"

#include <iostream>
using namespace std;
TaskExecuteComponent::TaskExecuteComponent()
{
    // currentTask to smart pointer ktory w tym momencie "przechowuje" nullptr
    if(currentTask.get() == nullptr && !currentTask)
        cout << "TaskExecuteComponent jest nullptr" << endl;
}

TaskExecuteComponent::TaskExecuteComponent(const TaskExecuteComponent & taskExecuteComponent)
{
    if(taskExecuteComponent.currentTask)
        currentTask = std::unique_ptr<Task>(taskExecuteComponent.currentTask->clone());
}

TaskExecuteComponent * TaskExecuteComponent::clone() const
{
    return new TaskExecuteComponent(*this);
}

Task * TaskExecuteComponent::getCurrentTask()
{
    return currentTask.get();
}

void TaskExecuteComponent::setCurrentTask(Task *task)
{
    // zwalniamy pamiec uzywana przez stary pointer i dajemy currentTask nowy pointer do przechowywania
    currentTask.reset(task);
}

void TaskExecuteComponent::acceptMessage(MessageType messageType)
{
    if(messageType == MessageType::destinationReached)
    {
        if(currentTask)
            currentTask->acceptTaskMessage(messageType);
    }
}

void TaskExecuteComponent::update(GameEntity & gameEntity)
{
    if(currentTask)
    {
        currentTask->update(gameEntity);
    }
}
