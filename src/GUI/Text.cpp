#include "Text.hpp"

// Constructor w/out Backdrop
TextBlock::TextBlock (string newText, sf::Font *newFont, const sf::Color newTextColor, int charSize, bool hasBorder, 
        sf::Vector2f position) {
    // Set the Text Formatting
    this->setCharacterSize(charSize);
    this->setPosition(position);
    this->setFillColor(newTextColor);
    if (hasBorder) {
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(1);
    }
    this->setFont(*newFont);
    this->setString(newText);
}


// Constructor w/out position
TextBlock::TextBlock (string newText, sf::Font *newFont, const sf::Color newTextColor, int charSize, bool hasBorder) {
    // Set the Text Formatting
    this->setCharacterSize(charSize);
    this->setFillColor(newTextColor);
    if (hasBorder) {
    this->setOutlineColor(sf::Color::Black);
    this->setOutlineThickness(1);
    }
    this->setFont(*newFont);
    this->setString(newText);
}


//Constructor w/Backdrop
TextBlock::TextBlock (string newText, sf::Font *newFont, const sf::Color newTextColor, int charSize, bool hasBorder, 
        sf::Vector2f position, sf::Color newBackdropColor, sf::Vector2f dimensions) {
    // Set the Text Formatting
    this->setString(newText);
    this->setCharacterSize(charSize);
    this->setFont(*newFont);
    this->setPosition (position.x + ((dimensions.x - this->getGlobalBounds().width) / 2 - 1),
            position.y + ((dimensions.y - charSize) / 2) - 7);
    this->setFillColor(newTextColor);
    if (hasBorder) {
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(1);
    }

    // Create the Backdrop Formatting
    this->backdrop.setSize(dimensions);
    this->backdrop.setPosition(position);
    this->backdrop.setFillColor(newBackdropColor);

    // Update Private Variable
    this->hasBackdrop = true;
}


const bool TextBlock::checkBackdrop () const {
    return this->hasBackdrop;
}


void TextBlock::setBackdrop (sf::Vector2f dimensions, sf::Color newColor, sf::Vector2f position, sf::Color border, float thickness) {
    this->hasBackdrop = true;
    this->backdrop.setPosition(position);
    this->backdrop.setSize(dimensions);
    this->backdrop.setFillColor(newColor);
    this->backdrop.setOutlineColor(border);
    this->backdrop.setOutlineThickness(thickness);
}


void TextBlock::render (sf::RenderTarget &window) {
    if (this->hasBackdrop) {
        window.draw(this->backdrop);
    }
    window.draw(*this);
}
