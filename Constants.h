#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
public:
    const static int TILE_WIDTH = 64;
    const static int TILE_HEIGHT = 64;
    const static int MAP_WIDTH = 100;
    const static int MAP_HEIGHT = 100;
    const static int FRAMES_PER_SECOND = 120;
    const static int GAME_SPEED = 1000 / FRAMES_PER_SECOND;
    const static int MAP_TILESET_GRAPHICS_OFFSET = 4;
    const static int MAP_TILESET_GRAPHICS_INITIAL_POSITION = 3;
};

#endif // CONSTATNS_H
