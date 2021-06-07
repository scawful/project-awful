#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"
#include "../Dungeon/DungeonGenerator.hpp"
#include "../GUI/Textbox.hpp"

class GameState: public State
{
private:
    // Variables
    DungeonGenerator *dungeonGenerator;
    Player *player;
    Sword *playerSword;

    std::vector<Enemy*> enemies;
    sf::RectangleShape enemySights[10];

    sf::Vector2f playerPosition;
    sf::Vector2f playerSize;
    sf::Vector2f swordPosition;

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
    void initEnemies();
    
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
