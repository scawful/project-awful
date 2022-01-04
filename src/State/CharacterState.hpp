#ifndef CharacterState_hpp
#define CharacterState_hpp

#include "State.hpp"

class CharacterState : public State
{
private:
    shared_ptr<sf::Event> sfEvent;

    // sfml Font Object 
    sf::Font characterFont;

    // sfml Text Object 
    sf::Text textboxOutput;

    // sfml Texture Object 
    sf::Texture backgroundTexture;

    // sfml RectangleShape Object 
    sf::RectangleShape background;

    // Custom Object Data Structures 
    std::map<std::string, Button*> buttons;
    std::map<std::string, Textbox*> textboxes;
    std::map<std::string, DropDown*> dropDownLists;
    std::map<std::string, TextBlock*> text_blocks;

    // Character Creation Substate 
    int current_substate;

    // GUI offsets 
    float gui_offset;
    float gui_size_x;
    float gui_size_y;

    // Initialization Functions 
    void initFonts();
    void initTextures();
    void initButtons();
    void initDropdowns();
    void initTextboxes();

public:
    CharacterState(sf::RenderWindow* window, std::stack<State*>* states, shared_ptr<sf::Event> event);
    virtual ~CharacterState();

    // Update Routines 
    void updateInput(const float& dt);
    void updateButtons();
    void updateDropdowns(const float& dt);
    void updateTextboxes();
    void neutralizeTextboxes();
    void update(const float& dt);

    // Render Routines 
    void renderButtons(sf::RenderTarget& target);
    void renderDropdowns(sf::RenderTarget& target);
    void renderTextbox(sf::RenderTarget& target);
    void renderSubStates(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif