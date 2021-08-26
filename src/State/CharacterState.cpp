#include "CharacterState.hpp"

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

void CharacterState::initButtons()
{
    this->buttons["CONFIRM_BTN"] = new Button(
                        sf::Vector2f((SCREEN_WIDTH - 250.f) / 2, (SCREEN_HEIGHT - 75.f) / 2), // position
                        sf::Vector2f(250.f, 75.f), // size 
                        &this->characterFont, "Confirm", 30, true,
                        sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color(0x56A5ECb3));
                        // idle                 hover                      active
                        // 0xRRGGBBAA 
                        // RRR, GGG, BBB, AAA
    
}


void CharacterState::initTextboxes () {
    this->textboxes["CHARACTER_NAME"] = new Textbox (
                        sf::Vector2f((SCREEN_WIDTH - 450.f) / 2, ((SCREEN_HEIGHT - 50.f) / 2) - 250.f),
                        sf::Vector2f(450.f, 50.f),
                        &this->characterFont, 30, 23, 
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color::Black,
                        sf::Color(225, 231, 238, 200), sf::Color(244, 244, 244, 200), sf::Color::White, true, "Enter Name");
}


CharacterState::CharacterState(sf::RenderWindow* window, std::stack<State*>* states, shared_ptr<sf::Event> event) : State(window, states)
{
    sfEvent = event;
    initFonts();
    initTextures();
    initButtons();
    initTextboxes();

}

CharacterState::~CharacterState() 
{
    for ( auto btn : buttons ) 
    {
        delete btn.second;
    }

    for ( auto txtbx : textboxes ) 
    {
        delete txtbx.second;
    }

}

void CharacterState::updateInput(const float &dt) 
{
    if (!this->getKeytime()) {
        this->updateKeytime(dt);
    }
}

void CharacterState::updateButtons()
{
    // Update all buttons in state and handles functionalty
    for (auto &it : this->buttons) 
    {
        it.second->update(this->mousePosView);
    }
    
    if ( this->buttons["CONFIRM_BTN"]->isPressed() )
    {
        this->endState();
    }
}


void CharacterState::updateTextboxes() 
{
    for (auto &it : this->textboxes)
    {
        it.second->update(this->mousePosView, *this->sfEvent.get());
    }
}


void CharacterState::neutralizeTextboxes () 
{
    for (auto &it : this->textboxes)
    {
        it.second->neutralize();
    }
}

void CharacterState::update(const float& dt) 
{
    this->updateKeytime(dt);
}

void CharacterState::render(sf::RenderTarget* target) 
{
    target->clear(sf::Color(100, 100, 100, 0));
}
