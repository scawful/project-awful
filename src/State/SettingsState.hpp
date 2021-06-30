#ifndef SettingsState_hpp
#define SettingsState_hpp

#include "State.hpp"

class SettingsState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font menu_font;
        
    std::map<std::string, Button*> buttons;
    std::map<std::string, DropDown*> dropDownLists;
            
    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    
public:
    SettingsState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~SettingsState();
    
    // Functions
    void getQuit();
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif /* SettingsState_hpp */