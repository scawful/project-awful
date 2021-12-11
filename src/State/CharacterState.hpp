#ifndef CharacterState_hpp
#define CharacterState_hpp

#include "State.hpp"

class CharacterState : public State
{
private:
    shared_ptr<sf::Event> sfEvent;
    sf::Font characterFont;
    sf::Text textboxOutput;
    sf::RectangleShape background;

    std::map<std::string, Button*> buttons;
    std::map<std::string, Textbox*> textboxes;
    std::map<std::string, DropDown*> dropDownLists;
    std::map<std::string, TextBlock*> text_blocks;

    int current_substate;
    float gui_offset;
    float gui_size_x;
    float gui_size_y;

    void initFonts();
    void initTextures();
    void initButtons();
    void initDropdowns();
    void initTextboxes();

public:
    CharacterState(sf::RenderWindow* window, std::stack<State*>* states, shared_ptr<sf::Event> event);
    virtual ~CharacterState();

    void updateInput(const float& dt);
    void updateButtons();
    void updateDropdowns(const float& dt);
    void updateTextboxes();
    void neutralizeTextboxes();

    // Functions    
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderDropdowns(sf::RenderTarget& target);
    void renderTextbox(sf::RenderTarget& target);
    void renderSubStates(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif