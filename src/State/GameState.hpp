#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"
#include "../Dungeon/DungeonGenerator.hpp"

enum world { UNDERWORLD, OVERWORLD };

class GameState: public State
{
private:
    // Variables
    World *currentWorld;
    Player *player;
    Sword *playerSword;
    DungeonGenerator *dungeonGenerator;

    std::vector<Enemy*> enemies;
    std::map<std::string, Button*> buttons;

    sf::Vector2f playerPosition;
    sf::Vector2f playerSize;
    sf::Vector2f swordPosition;

    sf::RectangleShape enemySights[10];
    sf::RectangleShape background;
    sf::RectangleShape enemyLineOfSight;
    sf::Texture playerTexture;
    sf::Texture floorTileTexture;
    sf::Event sfEvent; 
    sf::Font gameFont;

    // Functions
    void initFonts();
    void initTextures();
    void initPlayers();
    void initWorld();
    void initButtons();
    
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();
        
    // Functions
    void getQuit();
    
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif /* GameState_hpp */
