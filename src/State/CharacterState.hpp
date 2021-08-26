#ifndef CharacterState_hpp
#define CharacterState_hpp

#include "State.hpp"

class CharacterState : public State
{
private:
    shared_ptr<sf::Event> sfEvent;
    sf::Font characterFont;
    sf::Text textboxOutput;

    std::map<std::string, Button*> buttons;
    std::map<std::string, Textbox*> textboxes;

    void initFonts();
    void initTextures();
    void initButtons();
    void initTextboxes();

public:
    CharacterState(sf::RenderWindow* window, std::stack<State*>* states, shared_ptr<sf::Event> event);
    virtual ~CharacterState();

    void updateInput(const float& dt);
    void updateButtons();
    void updateTextboxes();
    void neutralizeTextboxes();

    // Functions    
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif