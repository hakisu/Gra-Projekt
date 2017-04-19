#ifndef ORDER_H
#define ORDER_H

#include <string>

class TaskExecuteSystem;

class Order
{
public:
    virtual ~Order() {};

    virtual void executeOrder(TaskExecuteSystem &taskExecuteSystem, int tileIndex) = 0;

    std::string getOrderText();

protected:
    std::string orderText;
};

class OrderCutTree : public Order
{
public:
    OrderCutTree();

    void executeOrder(TaskExecuteSystem &taskExecuteSystem, int tileIndex);
};

class OrderCancel : public Order
{
public:
    OrderCancel();

    void executeOrder(TaskExecuteSystem &taskExecuteSystem, int tileIndex);
};

#endif // ORDER_H
