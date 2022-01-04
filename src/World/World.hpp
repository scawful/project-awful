#ifndef World_hpp
#define World_hpp

#include "../core.hpp"
#include "../Actor/Player.hpp"
#include "../Actor/Enemy.hpp"
#include "../Ancilla/Sword.hpp"
#include "../Dungeon/DungeonGenerator.hpp"
#include "../GUI/Textbox.hpp"
#include "../GUI/DropDown.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Text.hpp"


class World
{
private:
    void initTextures();

protected:
    Player *player;
    sf::Vector2f playerPosition;
    sf::Vector2f playerSize;
    
    std::map<std::string, sf::Texture> textures;

public:
    World( Player *playerRef, std::map<std::string, sf::Texture> &textureRef );
    virtual ~World();
    
    // Virtual update routine 
    virtual void update(const float& dt) = 0;

    // Virtual render routine
    virtual void render(sf::RenderTarget& target) = 0;
};

#endif