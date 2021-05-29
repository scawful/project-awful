#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "State.hpp"

class MainMenuState : public State 
{
private:
    // Variables
    sf::Event sfEvent;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font menu_font;
                
    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    
public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~MainMenuState();
        
    // Functions
    void getQuit();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

};

#endif /* MainMenuState_hpp */
