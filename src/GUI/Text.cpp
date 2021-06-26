#include "Text.hpp"

TextBlock::TextBlock (string newText, sf::Font &newFont, int size) {
    this->setCharacterSize(size);
    this->setFont(newFont);
    this->setString(newText);
}

void TextBlock::setDefaultBackdrop(sf::Color color) {
    this->hasBackdrop = true;

    float xCord = this->getPosition().x - this->getString().getSize();
    float yCord = this->getPosition().y;
    this->backdrop.setPosition(sf::Vector2f(xCord, yCord));

    this->backdropDimensions.x = this->getString().getSize() * this->getCharacterSize() / 2 + this->getString().getSize() * 4;
    this->backdropDimensions.y = this->getCharacterSize() + 8.0;
    this->backdrop.setSize(this->backdropDimensions);

    this->backdrop.setFillColor(color);
}

void TextBlock::setCustomBackdrop (sf::Color color, sf::Vector2f dimensions) {
    this->hasBackdrop = true;
    this->backdropDimensions = dimensions;
    this->backdrop.setSize(this->backdropDimensions);
}

void TextBlock::setAdjustedBackdrop (sf::Color color, sf::Vector2f dimensions) {
    this->setDefaultBackdrop(color);

    this->backdropDimensions.x += dimensions.x;
    this->backdropDimensions.y += dimensions.y;
    this->backdrop.setSize(this->backdropDimensions);
}

void TextBlock::drawTextBlock (sf::RenderTarget &window) {
    if (this->hasBackdrop) {
        window.draw(this->backdrop);
    }
    window.draw(*this);
}
