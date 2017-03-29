#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
public:
    // ilosc plytek w mapie
    const static int MAP_WIDTH = 100;
    const static int MAP_HEIGHT = 100;

    // ilosc updatow silnika gry w ciagu sekundy
    const static unsigned int FRAMES_PER_SECOND = 30;
    const static unsigned int GAME_SPEED = 1000 / FRAMES_PER_SECOND;

    // stale do pliku map.png
    const static unsigned int TILE_WIDTH = 64;
    const static unsigned int TILE_HEIGHT = 64;
    const static unsigned int MAP_TILESET_GRAPHICS_OFFSET = 4;
    const static unsigned int MAP_TILESET_GRAPHICS_INITIAL_POSITION = 3;

    // wtepna ilosc obiektow do zarezerwowania
    const static unsigned int INITIAL_OBJECTS_RESERVED = 2;
};

#endif // CONSTANTS_H
