#include "Textbox.hpp"

// Constructor
Textbox::Textbox (sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, unsigned character_size, unsigned character_limit,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color, bool hasBorder, string dfltText = "")
            : limit(character_limit), isSelected(false) {
    
    this->box = new Button(position, dimensions, font, dfltText, character_size, hasBorder,
            text_idle_color, text_active_color, text_active_color,
            idle_color, hover_color, active_color);
}


// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->box->setString(this->box->getString() + static_cast<char>(CharTyped));
    } else if (CharTyped == DELETE_KEY) {
        if (this->box->getString().toUtf8().size() > 0) {
            deleteLastChar();
        }
    } else if (CharTyped == ESCAPE_KEY) {

    }

    this->box->setString(this->box->getString() + "_");
}


// Function for the 'BACKSPACE' Key
void Textbox::deleteLastChar () {
    // Transfer each character except the last one into a new string
    string origText = this->box->getString();
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }

    // Replace old string with new string (last character has been deleted)
    this->box->setString(newText);
}


void Textbox::setLimit (unsigned character_limit) {
    this->limit = character_limit;
}


const bool Textbox::getKeytime () {
    if (this->keytime >= this->keytimeMax) {
        this->keytime = 0.f;
        return true;
    }
    return false;
}


void Textbox::updateKeytime (const float& dt) {
    if ( this->keytime < this->keytimeMax ) {
        this->keytime += 10.f * dt;
    }
}


void Textbox::update (const sf::Vector2f &mousePos, const float& dt) {
    this->updateKeytime(dt);


}


void Textbox::render (sf::RenderTarget& target) {
    target.draw(*this->box);
}
