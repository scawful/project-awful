#include "Text.hpp"

TextBlock::TextBlock (string newText, sf::Font &newFont, int size) {
    this->setCharacterSize(size);
    this->setFont(newFont);
    this->setString(newText);
}

void TextBlock::setBackdrop(sf::Color color, sf::Vector2f dimensions) {
    this->hasBackdrop = true;
    this->backdrop.setPosition(this->getPosition());
    this->backdrop.setFillColor(color);
    this->backdrop.setSize(dimensions);
}

void TextBlock::drawTextBlock (sf::RenderTarget &window) {
    window.draw(*this);
    if (this->hasBackdrop) {
        window.draw(this->backdrop);
    }
}
