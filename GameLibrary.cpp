#include "GameLibrary.h"

namespace gl
{
    GameEntity createCharacter()
    {
        GameEntity a(0, 0, new GraphicsComponent());
        return a;
    }
}
