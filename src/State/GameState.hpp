#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"
#include "../Actor/Actor.hpp"

class GameState: public State
{
private:
    // Variables
    Actor *player;
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture playerTexture;
    sf::Event sfEvent;

    
    // Functions
    void initFonts();
    void initTextures();
    void initPlayers();
    
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();
        
    // Functions
    void getQuit();
    
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif /* GameState_hpp */
