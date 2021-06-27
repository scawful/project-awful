#include "Button.hpp"

Button::Button( sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
    this->buttonState = BTN_IDLE;
    
    this->shape.setPosition(sf::Vector2f(position.x, position.y));
    this->shape.setSize(sf::Vector2f(dimensions.x, dimensions.y));
    this->shape.setFillColor(idle_color);
    
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition( this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2, 
                            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2) - (this->text.getGlobalBounds().height));
    
    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
    
    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;
}


Button::~Button() {
    
}

const bool Button::isPressed() const 
{
    if ( this->buttonState == BTN_ACTIVE )
    {
        return true;
    }     

    return false;
}

const std::string Button::getText() const 
{
    return this->text.getString();
}

void Button::setText(const std::string text) 
{
    this->text.setString( text );    
}

void Button::update(const sf::Vector2f& mousePos) 
{
    // update booleans for hover and pressed
    this->buttonState = BTN_IDLE;
    
    if ( this->shape.getGlobalBounds().contains(mousePos) ) 
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
            this->shape.setFillColor(this->idleColor);
            this->text.setFillColor(this->textIdleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            this->text.setFillColor(this->textHoverColor);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            this->text.setFillColor(this->textActiveColor);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::Blue);
            break;
    }    
}

void Button::render(sf::RenderTarget& target) 
{
    target.draw(this->shape);
    target.draw(this->text);    
}
