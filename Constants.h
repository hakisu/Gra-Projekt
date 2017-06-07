#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>

namespace Constants
{
    // ilosc plytek w mapie
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;

    // ilosc updatow silnika gry w ciagu sekundy
    const unsigned int FRAMES_PER_SECOND = 60;
    const unsigned int GAME_SPEED = 1000 / FRAMES_PER_SECOND;

	// maksymalna liczba klatek graficznych na sekunde (0 oznacza brak limitu) oraz synchronizacja pionowa
	const unsigned int FRAME_RATE_LIMIT = 0;
	const bool VERTICAL_SYNC_ENABLED = false;

    // stale do pliku map.png
    const unsigned int TILE_WIDTH = 64;
    const unsigned int TILE_HEIGHT = 64;
    const unsigned int MAP_TILESET_GRAPHICS_OFFSET = 4;
    const unsigned int MAP_TILESET_GRAPHICS_INITIAL_POSITION = 3;

    // wtepna ilosc obiektow do zarezerwowania
    const unsigned int INITIAL_OBJECTS_RESERVED = 10;
	const unsigned int INITIAL_TREES_CREATED_MAXIMUM = 500;

	// wartosc alpha dla schematow budowania
	const unsigned int BLUEPRINT_ALPHA_VALUE = 50;

	// sciezki do plikow z grafikami
	const std::string graphicsPathToCharacter = "Graphics/character.png";
	const std::string graphicsPathToTreeSapling = "Graphics/tree_sapling.png";
	const std::string graphicsPathToTreeYoung = "Graphics/tree_young.png";
	const std::string graphicsPathToTreeOld = "Graphics/tree_old.png";
	const std::string graphicsPathToResourceTree = "Graphics/resource_tree.png";
	const std::string graphicsPathToWall = "Graphics/wall.png";

	// sciezki do plikow z czcionkami
	const std::string fontPathToOpenSans = "OpenSans-Regular.ttf";

	// stale dla debugowania
	const int DEBUG_DISPLAY_ALPHA_VALUE = 170;
}

#endif // CONSTANTS_H
