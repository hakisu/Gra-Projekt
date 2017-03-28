#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <vector>
#include <list>

#include "Component.h"
#include "Map.h"


class MovementComponent : public Component
{
private:
    class PathStep
    {
    public:
        int tileIndex;
        unsigned int pathScoreG;
        unsigned int pathScoreH;
        PathStep* parent;

        PathStep(int tileIndex, unsigned int pathScoreG, unsigned int pathScoreH, PathStep* parent = nullptr) : tileIndex(tileIndex), pathScoreG(pathScoreG), pathScoreH(pathScoreH), parent(parent) {}

        unsigned int getScoreF() { return pathScoreG + pathScoreH;}
    };

    int destinationTile;
    Map& gameMap;
    bool isPathCalculated = false;
    float movementSpeed;
    std::vector<int> path;

    void findNewPath(GameEntity& gameEntity);
    unsigned int getHeuristicDistance(int startTileIndex, int endTileIndex);

public:
    MovementComponent(Map& gameMap);

    const std::vector<int>& getPath() const;

    virtual void update(GameEntity& gameEntity);
    void setDestinationTile(int tileIndex);
};

#endif // MOVEMENT_COMPONENT_H
