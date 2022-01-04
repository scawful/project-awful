#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"
#include "../Dungeon/DungeonGenerator.hpp"

enum world { UNDERWORLD, OVERWORLD };

class GameState: public State
{
private:
    // Game Variables
    World *currentWorld;
    Player *player;
    Sword *playerSword;

    // Data Structures for Custom Objects 
    std::vector<Enemy*> enemies;
    std::map<std::string, Button*> buttons;

    // sfml Font Object
    sf::Font gameFont;

    // sfml Event Object 
    sf::Event sfEvent; 

    // sfml Vector Objects 
    sf::Vector2f playerPosition;
    sf::Vector2f playerSize;
    sf::Vector2f swordPosition;

    // sfml Rectangle Objects 
    sf::RectangleShape enemySights[10];
    sf::RectangleShape background;
    sf::RectangleShape enemyLineOfSight;

    // sfml Texture Objects
    sf::Texture playerTexture;
    sf::Texture floorTileTexture;

    // Initialization functions
    void initFonts();
    void initTextures();
    void initPlayers();
    void initWorld();
    void initButtons();
    
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();
        
    // Accessors
    void getQuit();
    
    // Update routines 
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);

    // Render routines 
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif /* GameState_hpp */
