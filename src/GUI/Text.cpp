#include "Text.hpp"

// Constructor w/out Backdrop
TextBlock::TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, int charSize) {
    // Set the Text Formatting
    this->setCharacterSize(charSize);
    this->setPosition(position);
    this->setFillColor(newTextColor);
    this->setOutlineColor(sf::Color::Black);
    this->setOutlineThickness(1);
    this->setFont(newFont);
    this->setString(newText);

    // Update Private variables;
    this->font = newFont;
    this->textColor = newTextColor;
}


//Constructor w/Backdrop
TextBlock::TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, int charSize, sf::Color newBackdropColor, sf::Vector2f dimensions) {
    // Set the Text Formatting
    this->setString(newText);
    this->setCharacterSize(charSize);
    this->setFont(newFont);
    this->setPosition (position.x + ((dimensions.x - this->getGlobalBounds().width) / 2 - 1),
            position.y + ((dimensions.y - charSize) / 2) - 7);
    this->setFillColor(newTextColor);
    // Create the Backdrop Formatting
    this->backdrop.setSize(dimensions);
    this->backdrop.setPosition(position);
    this->backdrop.setFillColor(newBackdropColor);

    // Update Private Variables
    this->font = newFont;
    this->textColor = newTextColor;
    this->hasBackdrop = true;
    this->backdropColor = newBackdropColor;
    this->backdropDimensions = dimensions;
}


const string TextBlock::getText() const {
    return this->getString();
}


void TextBlock::setText(const string newText) {
    this->setString(newText);
}


void TextBlock::setBackdrop (sf::Vector2f dimensions, sf::Color newColor, sf::Vector2f position) {
    this->hasBackdrop = true;
    this->backdrop.setPosition(position);
    this->backdropDimensions = dimensions;
    this->backdrop.setSize(this->backdropDimensions);

    this->backdropColor = newColor;
    this->backdrop.setFillColor(newColor);
}


void TextBlock::setBackdropColor (sf::Color newColor) {
    this->backdropColor = newColor;
    this->backdrop.setFillColor(newColor);
}


void TextBlock::render (sf::RenderTarget &window) {
    if (this->hasBackdrop) {
        window.draw(this->backdrop);
    }
    window.draw(*this);
}
