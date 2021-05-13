
#ifndef Game_hpp
#define Game_hpp

#include "core.hpp"
#include "State/MainMenuState.hpp"

class Game {
private:
    // Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Image icon;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;
    
    sf::Clock dtClock;
    float dt;
    
    std::stack<State*> states;
    
    std::map<std::string, int> supportedKeys;

    // Initializations
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();
    
public:
    // Constructors / Destructors
    Game();
    virtual ~Game();
    
    // Functions
    
    // Update
    void updateDt();
    void updateSFMLEvents();
    void update();
    
    // Render
    void render();
    
    // Core 
    void run();
};

#endif /* Game_hpp */
