#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "State.hpp"

class MainMenuState : public State 
{
private:
    // Variables
    shared_ptr<sf::Event> sfEvent;

    // sfml Texture Object 
    sf::Texture backgroundTexture;

    // sfml RectangleShape Object
    sf::RectangleShape background;

    // sfml Font Object
    sf::Font menu_font;

    // Custom Object Maps 
    std::map<std::string, Button*> buttons;
    std::map<std::string, Textbox*> textboxes;
                
    // Initialization Functions 
    void initVariables();
    void initBackground();
    void initFonts();
    void initButtons();
    void initTextboxes();
    
public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, shared_ptr<sf::Event> Event);
    virtual ~MainMenuState();
        
    // Functions
    void getQuit();

    // Update routines 
    void updateInput(const float& dt);
    void updateButtons();
    void updateTextboxes();
    void neutralizeTextboxes();
    void update(const float& dt);

    // Render routines 
    void renderButtons(sf::RenderTarget& target);
    void renderTextbox(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

};

#endif /* MainMenuState_hpp */
