#ifndef Overworld_hpp
#define Overworld_hpp

#include "World.hpp"

class Overworld : public World
{
private:
    void initTextures();
    void initEnemies();

public:
    Overworld();
    ~Overworld();

    void update(const float& dt);
    void render(sf::RenderTarget &target);

};

#endif