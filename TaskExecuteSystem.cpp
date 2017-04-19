#include "TaskExecuteSystem.h"

#include <typeinfo>

#include "GameEntity.h"
#include "GameLibrary.h"
#include "Map.h"
#include "TaskExecuteComponent.h"

#include <iostream>
using namespace std;

TaskExecuteSystem::TaskExecuteSystem()
{

}

void TaskExecuteSystem::addTask(Task *task)
{
    for(auto &i : pendingTasksContainer)
    {
        if(i->tileIndex == task->tileIndex)
        {
            if(typeid(*i) == typeid(*task))
            {
                return;
            }
        }
    }

    pendingTasksContainer.emplace_back(task);
}

void TaskExecuteSystem::cancelTask(int tileIndex)
{
    for(auto &i : pendingTasksContainer)
    {
        if(i->tileIndex == tileIndex)
        {
            // usuwam dany Task z kontenera podmieniajac go z ostatnim i usuwajac ostatni element kontenera
            i = std::move(pendingTasksContainer.back());
            pendingTasksContainer.pop_back();
            break;
        }
    }
}

void TaskExecuteSystem::update(std::vector<GameEntity>& objects, Map &gameMap)
{
    if(pendingTasksContainer.size() > 0)
    {
        for(auto taskIterator = pendingTasksContainer.begin(); taskIterator != pendingTasksContainer.end(); ++taskIterator)
        {
            int minimalDistance = std::numeric_limits<int>::max();
            TaskExecuteComponent *bestTaskExecuteComponentPtr = nullptr;
            TaskExecuteComponent *taskExecuteComponentPtr = nullptr;

            for(auto &gameEntityReference : objects)
            {
                for(auto &componentPtr : gameEntityReference.components)
                {
                    if(typeid(*componentPtr) == typeid(TaskExecuteComponent))
                    {
                        taskExecuteComponentPtr = static_cast<TaskExecuteComponent*>(componentPtr.get());

                        if(taskExecuteComponentPtr->getCurrentTask() == nullptr)
                        {
                            int startTileIndex = gl::calculateTileIndex(gameEntityReference.getPosX(), gameEntityReference.getPosY());
                            int endTileIndex = (*taskIterator)->tileIndex;

                            if(gameMap.getAreaNumber(startTileIndex) == gameMap.getAreaNumber(endTileIndex))
                            {
                                int distance = gl::calculateHeuristicDistance(startTileIndex, endTileIndex);

                                if(distance < minimalDistance)
                                {
                                    bestTaskExecuteComponentPtr = taskExecuteComponentPtr;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            if(bestTaskExecuteComponentPtr != nullptr)
            {
                bestTaskExecuteComponentPtr->setCurrentTask((*taskIterator).release());
                pendingTasksContainer.erase(taskIterator);
                // po uzyciu erase iterator taskIterator jest niewlasciwy i manualnie go przestawiam, aby wskazywal w odpowiednie miejsce
                taskIterator--;
            }
        }
    }
}
