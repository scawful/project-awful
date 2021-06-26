#ifndef Underworld_hpp
#define Underworld_hpp

#include "World.hpp"

class Underworld : public World
{
private:
    DungeonGenerator *dungeonGenerator;

    void initTextures();
    void initPlayers();
    void initEnemies();

public:
    Underworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef );
    ~Underworld();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget &target);
};

#endif