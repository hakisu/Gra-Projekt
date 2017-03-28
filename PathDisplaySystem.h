#ifndef PATH_DISPLAY_SYSTEM_H
#define PATH_DISPLAY_SYSTEM_H

class GameEntity;
namespace sf
{
    class RenderWindow;
}

class PathDisplaySystem
{
private:

public:
    static void render(GameEntity& gameEntity, sf::RenderWindow& window);
};

#endif // PATH_DISPLAY_SYSTEM_H
