#ifndef Underworld_hpp
#define Underworld_hpp

#include "World.hpp"

class Underworld : public World
{
private:
    void initTextures();
    void initEnemies();

public:
    Underworld();
    ~Underworld();

    void update(const float& dt);
    void render(sf::RenderTarget &target);
};

#endif