#include "Button.hpp"

Button::Button( sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, std::string text, unsigned character_size, bool hasBorder,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
    this->buttonState = BTN_IDLE;
    
    this->setBackdrop(sf::Vector2f(dimensions.x, dimensions.y), idle_color, sf::Vector2f(position.x, position.y), active_color, 1);
    this->setFont(*font);
    this->setString(text);
    this->setFillColor(text_idle_color);
    this->setCharacterSize(character_size);
    this->setPosition(position.x + ((dimensions.x - this->getGlobalBounds().width) / 2 - 1),
            position.y + ((dimensions.y - character_size) / 2) - 5);
    if (hasBorder) {
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(1);
    }

    // Update Private Variables
    this->assignColors(text_idle_color, text_hover_color, text_active_color, idle_color, hover_color, active_color);
}


const bool Button::isPressed() const 
{
    if ( this->buttonState == BTN_ACTIVE )
    {
        return true;
    }     

    return false;
}


void Button::assignColors (sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color) {
    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
}


void Button::update(const sf::Vector2f& mousePos) 
{
    // update booleans for hover and pressed
    this->buttonState = BTN_IDLE;
    
    if ( this->backdrop.getGlobalBounds().contains(mousePos) ) 
    {
        this->buttonState = BTN_HOVER;
        
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) 
        {
            this->buttonState = BTN_ACTIVE;
        }
    }
    
    switch ( this->buttonState ) 
    {
        case BTN_IDLE:
            this->backdrop.setFillColor(this->idleColor);
            this->setFillColor(this->textIdleColor);
            break;
        case BTN_HOVER:
            this->backdrop.setFillColor(this->hoverColor);
            this->setFillColor(this->textHoverColor);
            break;
        case BTN_ACTIVE:
            this->backdrop.setFillColor(this->activeColor);
            this->setFillColor(this->textActiveColor);
            break;
        default:
            this->backdrop.setFillColor(sf::Color::Red);
            this->setFillColor(sf::Color::Blue);
            break;
    }    
}


void Button::render(sf::RenderTarget& target) 
{
    if (this->checkBackdrop()) {
        target.draw(this->backdrop);
    }
    target.draw(*this);    
}

