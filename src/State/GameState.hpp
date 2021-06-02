#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"
#include "../Dungeon/DungeonGenerator.hpp"

class GameState: public State
{
private:
    // Variables
    DungeonGenerator *dungeonGenerator;
    Player *player;
    Enemy *enemy;
    sf::RectangleShape background;
    sf::RectangleShape enemyLineOfSight;
    sf::Texture playerTexture;
    sf::Texture floorTileTexture;
    sf::Event sfEvent; 
    sf::Font font;

    // Functions
    void initFonts();
    void initTextures();
    void initPlayers();
    
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();
        
    // Functions
    void getQuit();
    
    void updateEnemyAI(const float& dt);
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif /* GameState_hpp */
