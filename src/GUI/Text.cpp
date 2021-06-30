#include "Text.hpp"

// Constructor w/out Backdrop
TextBlock::TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, unsigned int charSize) {
    // Set the Text Formatting
    this->setCharacterSize(charSize);
    this->setPosition(position);
    this->setColor(newTextColor);
    this->setOutlineColor(sf::Color::Black);
    this->setOutlineThickness(1);
    this->setFont(newFont);
    this->setString(newText);

    // Update Private variables;
    this->font = newFont;
    this->textColor = newTextColor;
}

//Constructor w/Backdrop
TextBlock::TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, unsigned int charSize,
    sf::Color newBackdropColor, sf::Vector2f dimensions) {
    // Set the Text Formatting
    this->setPosition(position);
    this->setCharacterSize(charSize);
    this->setFont(newFont);
    this->setString(newText);
    this->setColor(newTextColor);

    // Create the Backdrop Formatting
    this->backdrop.setSize(dimensions);
    this->backdrop.setPosition(position.x - ((dimensions.x - this->getGlobalBounds().width) / 2),
                            position.y - ((dimensions.y - this->getGlobalBounds().height) / 2) + this->getGlobalBounds().height / 2);
    this->backdrop.setFillColor(newBackdropColor);

    // Update Private Variables
    this->font = newFont;
    this->textColor = newTextColor;
    this->hasBackdrop = true;
    this->backdropColor = newBackdropColor;
    this->backdropDimensions = dimensions;
}

void TextBlock::setCustomBackdrop (sf::Vector2f dimensions) {
    this->hasBackdrop = true;
    this->backdropDimensions = dimensions;
    this->backdrop.setSize(this->backdropDimensions);
}

void TextBlock::render (sf::RenderTarget &window) {
    if (this->hasBackdrop) {
        window.draw(this->backdrop);
    }
    window.draw(*this);
}
