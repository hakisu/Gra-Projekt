#include "MovementComponent.h"

#include <iostream>

#include "GameEntity.h"
#include "Constants.h"
#include "RandomNumberGenerator.h"

MovementComponent::MovementComponent(Map& gameMap) : gameMap(gameMap)
{
//    this->movementSpeed = RandomNumberGenerator::getIntNumber(1, 20);
    this->movementSpeed = 10;
    destinationTile = RandomNumberGenerator::getIntNumber(0, Constants::MAP_WIDTH * Constants::MAP_HEIGHT - 1);
}

void MovementComponent::update(GameEntity& gameEntity)
{
    if(!isPathCalculated)
    {
        findNewPath(gameEntity);
    }

    if(path.size() > 0)
    {
        // flagi oznaczajace czy polozenie X i Y nowej plytki zostalo osiagniete przez komponent ruchu
        bool posXAchieved = false, posYAchieved = false;

        float currentPosX = gameEntity.getPosX();
        float currentPosY = gameEntity.getPosY();
        float destinationPosX = path.back() % Constants::MAP_WIDTH * Constants::TILE_WIDTH;
        float destinationPosY = path.back() / Constants::MAP_WIDTH * Constants::TILE_HEIGHT;

        if(currentPosX + movementSpeed < destinationPosX)
        {
            gameEntity.setPosX(currentPosX + movementSpeed);
            gameEntity.setCurrentChangeInPosX(movementSpeed);
        }
        else if(currentPosX - movementSpeed > destinationPosX)
        {
            gameEntity.setPosX(currentPosX - movementSpeed);
            gameEntity.setCurrentChangeInPosX(-movementSpeed);
        }
        else
        {
            posXAchieved = true;

            if((path.size() > 1 && (*(path.rbegin() + 1) % Constants::MAP_WIDTH) == (path.back() % Constants::MAP_WIDTH)) || path.size() == 1)
            {
                gameEntity.setCurrentChangeInPosX(0);
                gameEntity.setPosX(destinationPosX);
            }
            else
            {
                gameEntity.setPosX(currentPosX + gameEntity.getCurrentChangeInPosX());
            }
        }

        if(currentPosY + movementSpeed < destinationPosY)
        {
            gameEntity.setPosY(currentPosY + movementSpeed);
            gameEntity.setCurrentChangeInPosY(movementSpeed);
        }
        else if(currentPosY - movementSpeed > destinationPosY)
        {
            gameEntity.setPosY(currentPosY - movementSpeed);
            gameEntity.setCurrentChangeInPosY(-movementSpeed);
        }
        else
        {
            posYAchieved = true;

            if((path.size() > 1 && (*(path.rbegin() + 1) / Constants::MAP_WIDTH) == (path.back() / Constants::MAP_WIDTH)) || path.size() == 1)
            {
                gameEntity.setCurrentChangeInPosY(0);
                gameEntity.setPosY(destinationPosY);
            }
            else
            {
                gameEntity.setPosY(currentPosY + gameEntity.getCurrentChangeInPosY());
            }
        }

        if(posXAchieved && posYAchieved)
        {
            if(path.front() != destinationTile)
            {
                isPathCalculated = false;
                std::cout << "PosX and PosY achieved " << " front to : " << path.front() << " dest to : " << destinationTile << " Request to find new path sent!\n";
            }
            else
                path.pop_back();
        }
    }
}

void MovementComponent::setDestinationTile(int tileIndex)
{
    this->destinationTile = tileIndex;
    if(path.size() == 0)
    {
        isPathCalculated = false;
    }
}

unsigned int MovementComponent::getHeuristicDistance(int startTileIndex, int endTileIndex)
{
    int startPosX = startTileIndex % Constants::MAP_WIDTH;
    int startPosY = startTileIndex / Constants::MAP_HEIGHT;
    int endPosX = endTileIndex % Constants::MAP_WIDTH;
    int endPosY = endTileIndex / Constants::MAP_WIDTH;

    return std::abs(endPosX - startPosX) + std::abs(endPosY - startPosY);
}

void MovementComponent::findNewPath(GameEntity& gameEntity)
{
    std::cout << "findNewPath() with ";
    std::cout << gameEntity.getPosX() << " " << gameEntity.getPosY() << " -> ";

    std::list<PathStep> closedList;
    std::list<PathStep> openList;

    int endTileIndex = destinationTile;
    int startPosX = gameEntity.getPosX() / Constants::TILE_WIDTH;
    int startPosY = gameEntity.getPosY() / Constants::TILE_HEIGHT;
    // indeks w tablicy 1-wymiarowej z ktorego zaczynamy szukac drogi do indeksu endTileIndex
    int startTileIndex = startPosX + startPosY * Constants::MAP_WIDTH;

    openList.emplace_front(startTileIndex, 0, 0);

    PathStep* currentStep = nullptr;

    bool pathFound = false;

    while(openList.size() > 0)
    {
        currentStep = &openList.front();

        closedList.emplace_back(currentStep->tileIndex, currentStep->pathScoreG, currentStep->pathScoreH, currentStep->parent);
        openList.pop_front();

        currentStep = &closedList.back();

        if(currentStep->tileIndex == endTileIndex)
        {
            pathFound = true;
            break;
        }

        // dodajemy wszystkie poprawne, sasiadujace z naszym obecnym kafelkiem kafelki do kontenera adjacentTilesIndexes
        std::vector<int> adjacentTilesIndexes;
        adjacentTilesIndexes.reserve(4);
        int currentTileIndex = currentStep->tileIndex;

        // plytka gorna
        if(gameMap.isWalkable(currentTileIndex - Constants::MAP_WIDTH) && currentTileIndex - Constants::MAP_WIDTH > 0)
            adjacentTilesIndexes.emplace_back(currentTileIndex - Constants::MAP_WIDTH);
        // plytka prawa
        if(gameMap.isWalkable(currentTileIndex + 1) && ((currentTileIndex + 1) % Constants::MAP_WIDTH) != 0)
            adjacentTilesIndexes.emplace_back(currentTileIndex + 1);
        // plytka dolna
        if(gameMap.isWalkable(currentTileIndex + Constants::MAP_WIDTH) && currentTileIndex + Constants::MAP_WIDTH < Constants::MAP_WIDTH * Constants::MAP_HEIGHT)
            adjacentTilesIndexes.emplace_back(currentTileIndex + Constants::MAP_WIDTH);
        // plytka lewa
        if(gameMap.isWalkable(currentTileIndex -1) && (currentTileIndex % Constants::MAP_WIDTH) != 0)
            adjacentTilesIndexes.emplace_back(currentTileIndex - 1);

        // wykonujemy dla kazdego pola sasiadujacego (przechodzimy przez caly kontener adjacentTilesIndexes)
        for(unsigned int i = 0; i < adjacentTilesIndexes.size(); ++i)
        {
            // sprawdzamy czy dany kafelek z tych sasiadujacych byl juz w zamknietej liscie
            bool isInClosedList = false;
            for(auto it = closedList.begin(); it != closedList.end(); ++it)
            {
                if((*it).tileIndex == adjacentTilesIndexes[i])
                {
                    isInClosedList = true;
                    break;
                }
            }
            if(isInClosedList)
                continue;

            // sprawdzamy czy dany kafelek z tych sasiadujacych byl juz w otwartej liscie
            bool isInOpenList = false;
            PathStep* adjacentTile = nullptr;

            for(auto it = openList.begin(); it != openList.end(); ++it)
            {
                if((*it).tileIndex == adjacentTilesIndexes[i])
                {
                    isInOpenList = true;
                    adjacentTile = &(*it);
                    break;
                }
            }
            if(!isInOpenList)
            {
                if(openList.size() == 0)
                {
                    openList.emplace_front(adjacentTilesIndexes[i], currentStep->pathScoreG + 1, getHeuristicDistance(adjacentTilesIndexes[i], endTileIndex), currentStep);
                }
                else if(openList.back().getScoreF() < getHeuristicDistance(adjacentTilesIndexes[i], endTileIndex) + currentStep->pathScoreG + 1)
                {
                    openList.emplace_back(adjacentTilesIndexes[i], currentStep->pathScoreG + 1, getHeuristicDistance(adjacentTilesIndexes[i], endTileIndex), currentStep);
                }
                else
                {
                    for(auto it = openList.begin(); it != openList.end(); ++it)
                    {
                        if((*it).getScoreF() >= getHeuristicDistance(adjacentTilesIndexes[i], endTileIndex) + currentStep->pathScoreG + 1)
                        {
                            openList.emplace(it, adjacentTilesIndexes[i], currentStep->pathScoreG + 1,
                                             getHeuristicDistance(adjacentTilesIndexes[i], endTileIndex), currentStep);
                            break;
                        }
                    }
                }
            }
            else
            {
                if(currentStep->pathScoreG + 1 <= adjacentTile->pathScoreG)
                {
                    adjacentTile->pathScoreG = currentStep->pathScoreG + 1;
                    adjacentTile->parent = currentStep;
                }
            }
        }
    }

    path.clear();

    if(pathFound)
    {
        while(currentStep->parent != nullptr)
        {
            path.emplace_back(currentStep->tileIndex);
            currentStep = currentStep->parent;
        }
    }
    else
        this->destinationTile = startTileIndex;

    isPathCalculated = true;

    std::cout << " findNewPath() finished\n";
}

const std::vector<int>& MovementComponent::getPath() const
{
    return path;
}
