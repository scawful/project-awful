#ifndef SettingsState_hpp
#define SettingsState_hpp

#include "State.hpp"

class SettingsState : public State
{
private:
    // sfml Texture Object 
    sf::Texture backgroundTexture;

    // sfml RectangleShape Object 
    sf::RectangleShape background;

    // sfml Font Object 
    sf::Font menu_font;
        
    // Custom Object Data Structures 
    std::map<std::string, Button*> buttons;
    std::map<std::string, DropDown*> dropDownLists;
    std::map<std::string, int>* supportedKeys;
            
    // Initialization functions 
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    
public:
    SettingsState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~SettingsState();
    
    // Accessors
    void getQuit();

    // Update routines 
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    // Render routines 
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif /* SettingsState_hpp */