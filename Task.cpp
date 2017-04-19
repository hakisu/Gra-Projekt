#include "Task.h"

#include "GameEntity.h"
#include "GameLibrary.h"
#include "MovementComponent.h"
#include "TaskExecuteComponent.h"

#include <iostream>
using namespace std;

Task::Task(int tileIndex)
{
    this->tileIndex = tileIndex;
}

TaskCutTree::TaskCutTree(int tileIndex) : Task(tileIndex)
{
}

void TaskCutTree::acceptTaskMessage(MessageType messageType)
{
    if(messageType == MessageType::destinationReached)
    {
        cout << "ok!!!!!!!" << endl;
        destinationReached = true;
    }
}

void TaskCutTree::update(GameEntity & gameEntity)
{
    if(!pathSet)
    {
        auto ptr = gl::getComponentPtr<MovementComponent>(gameEntity);
        ptr->setDestinationTile(tileIndex);
        pathSet = true;
        cout << "path set " << endl;
    }
    // wykonywanie zadania zakonczone, usuwamy obiekt zarzadzany przez currentTask (czyli ten obiekt)
    else if(taskFinished)
    {
        gl::getComponentPtr<TaskExecuteComponent>(gameEntity)->setCurrentTask();
        cout << "task finished" << endl;
    }
    else if(taskBeingPerformed)
    {
        taskFinished = true;
        cout << "taskbeingperformed" << endl;
    }
    else if(destinationReached)
    {
        taskBeingPerformed = true;
        cout << "destinationReached" << endl;
    }
}
