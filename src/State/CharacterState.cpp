#include "CharacterState.hpp"
#include "../GUI/Textbox.hpp"

void CharacterState::initFonts() 
{
    if (!this->characterFont.loadFromFile("../assets/ARCADECLASSIC.TTF")) 
    {
        cout << "Error couldn't load character font" << "\n";
    }  
}

void CharacterState::initTextures() 
{
    
}

CharacterState::CharacterState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->initFonts();
    this->initTextures();

}

CharacterState::~CharacterState() 
{
    
}

void CharacterState::update(const float& dt) 
{
    this->updateKeytime(dt);
}

void CharacterState::render(sf::RenderTarget* target) 
{
    target->clear(sf::Color(100, 100, 100, 0));
}
