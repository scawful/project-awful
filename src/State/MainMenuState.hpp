#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "State.hpp"

class MainMenuState : public State 
{
private:
    // Variables
    sf::Event *sfEvent;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font menu_font;

    std::map<std::string, Button*> buttons;
    std::map<std::string, Textbox*> textboxes;
                
    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initButtons();
    void initTextboxes();
    
public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, sf::Event *Event);
    virtual ~MainMenuState();
        
    // Functions
    void getQuit();
    void updateInput(const float& dt);
    void updateButtons();
    void updateTextboxes();
    void neutralizeTextboxes();
    void update(const float& dt);

    void renderButtons(sf::RenderTarget& target);
    void renderTextbox(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

};

#endif /* MainMenuState_hpp */
