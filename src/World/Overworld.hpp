#ifndef Overworld_hpp
#define Overworld_hpp

#include "World.hpp"

class Overworld : public World
{
private:
    std::vector<Enemy*> enemies;

    sf::RectangleShape enemySights[10];
    sf::RectangleShape background;
    sf::Texture floorTileTexture;
    sf::Font gameFont;

    void initFonts();
    void initTextures();
    void initPlayers();
    void initEnemies();

public:
    Overworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef );
    ~Overworld();

    void updateEnemyAI(const float& dt);
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget &target);

};

#endif