#include "PhysicsComponent.h"
#include "GameEntity.h"

#include <iostream>
#include "Constants.h"
#include "RandomNumberGenerator.h"

PhysicsComponent::PhysicsComponent()
{
    this->movementSpeed = RandomNumberGenerator::getIntNumber(1, 20);
    destinationTile = RandomNumberGenerator::getIntNumber(0, Constants::MAP_WIDTH * Constants::MAP_HEIGHT - 1);
    std::cout << movementSpeed << std::endl;
}

void PhysicsComponent::update(GameEntity& gameEntity)
{
    double destinationPosX = destinationTile % Constants::MAP_WIDTH * Constants::TILE_WIDTH;
    double destinationPosY = destinationTile / Constants::MAP_WIDTH * Constants::TILE_HEIGHT;

    if(std::floor(gameEntity.posX + movementSpeed) < destinationPosX)
    {
        gameEntity.posX += movementSpeed;
    }
    else if(std::floor(gameEntity.posX - movementSpeed) > destinationPosX)
    {
        gameEntity.posX -= movementSpeed;
    }
    else
    {
        gameEntity.posX = destinationPosX;
    }
    if(std::floor(gameEntity.posY + movementSpeed) < destinationPosY)
    {
        gameEntity.posY += movementSpeed;
    }
    else if(std::floor(gameEntity.posY - movementSpeed) > destinationPosY)
    {
        gameEntity.posY -= movementSpeed;
    }
    else
    {
        gameEntity.posY = destinationPosY;
    }

    if(gameEntity.posX == destinationPosX && gameEntity.posY == destinationPosY)
    {
        destinationTile = RandomNumberGenerator::getIntNumber(0, Constants::MAP_WIDTH * Constants::MAP_HEIGHT - 1);
    }
}
