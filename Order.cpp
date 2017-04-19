#include "Order.h"

#include "TaskExecuteSystem.h"

std::string Order::getOrderText()
{
    return orderText;
}

OrderCutTree::OrderCutTree()
{
    orderText = "Zetnij drzewo";
}

void OrderCutTree::executeOrder(TaskExecuteSystem &taskExecuteSystem, int tileIndex)
{
    taskExecuteSystem.addTask(new TaskCutTree(tileIndex));
}

OrderCancel::OrderCancel()
{
    orderText = "Anuluj";
}

void OrderCancel::executeOrder(TaskExecuteSystem &taskExecuteSystem, int tileIndex)
{
    taskExecuteSystem.cancelTask(tileIndex);
}

