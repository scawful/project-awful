#ifndef CharacterState_hpp
#define CharacterState_hpp

#include "State.hpp"

class CharacterState : public State
{
private:
    void initFonts();
    void initTextures();
    sf::Font characterFont;
    sf::Text textboxOutput;

public:
    CharacterState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~CharacterState();

    // Functions    
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif