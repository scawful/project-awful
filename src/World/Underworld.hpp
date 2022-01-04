#ifndef Underworld_hpp
#define Underworld_hpp

#include "World.hpp"

class Underworld : public World
{
private:
    int wallWidth;
    DungeonGenerator *dungeonGenerator;
    sf::Font gameFont;

    // Initialization functions
    void initTextures();
    void initFonts();
    void initDungeon();
    void initPlayers();

public:
    Underworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef );
    ~Underworld();

    // Update routines
    void updateInput(const float& dt);
    void update(const float& dt);

    // Render routines
    void render(sf::RenderTarget &target);
};

#endif