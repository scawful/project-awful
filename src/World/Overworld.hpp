#ifndef Overworld_hpp
#define Overworld_hpp

#include "World.hpp"

class Overworld : public World
{
private:
    // List of all Enemies in the Overworld
    std::vector<Enemy*> enemies;

    // sfml Objects
    sf::RectangleShape enemySights[10];
    sf::RectangleShape background;
    sf::Texture floorTileTexture;
    sf::Font gameFont;

    // Initialization functions 
    void initFonts();
    void initTextures();
    void initPlayers();
    void initEnemies();

public:
    Overworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef );
    ~Overworld();

    // Update routines 
    void updateEnemyAI(const float& dt);
    void updateInput(const float& dt);
    void update(const float& dt);

    // Render routines 
    void render(sf::RenderTarget &target);

};

#endif