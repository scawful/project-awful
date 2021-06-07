#ifndef World_hpp
#define World_hpp

#include "../core.hpp"
#include "../Actor/Player.hpp"
#include "../Actor/Enemy.hpp"
#include "../Ancilla/Sword.hpp"
#include "../Dungeon/DungeonGenerator.hpp"

class World
{
private:
    Player *player;

    void initTextures();
    void initEnemies();

public:
    World();
    virtual ~World();

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif