#include "Text.hpp"

Text::Text (string newText, sf::Font newFont, int size, sf::Color &color, sf::Vector2f newPos) {
    this->textbox.setCharacterSize(size);
    this->textbox.setColor(color);
    this->textbox.setFont(newFont);
    this->textbox.setString(newText);
    this->text << newText;
    this->pos = newPos;
}

void Text::setText (string newText) {
    if (this->text.str().length() > 0) {
        this->text.str("");
    }
    this->text << newText;
    this->textbox.setString(text.str());
}

void Text::setPosition (sf::Vector2f newPos) {
    this->pos = newPos;
    this->textbox.setPosition(newPos);
    if (this->hasBackdrop) {
        this->backdrop.setPosition(newPos);
    }
}

void Text::setBackdrop(sf::Color &color, sf::Vector2f dimensions) {
    this->hasBackdrop = true;
    this->backdrop.setPosition(this->pos);
    this->backdrop.setFillColor(color);
    this->backdrop.setSize(dimensions);
}

void Text::drawText (sf::RenderTarget &window) {
    window.draw(textbox);
    if (this->hasBackdrop) {
        window.draw(backdrop);
    }
}
