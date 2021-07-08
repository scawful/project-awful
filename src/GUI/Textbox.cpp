#include "Textbox.hpp"

// Constructor
Textbox::Textbox (sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, unsigned character_size, unsigned character_limit,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color, string dfltText = "") {
    
    // Apply Backdrop Styling
    this->assignColors(text_idle_color, text_hover_color, text_active_color,
            idle_color, hover_color, active_color);
    this->backdrop.setPosition(position);
    this->backdrop.setSize(dimensions);


    // Apply Text Styling
    this->setString(dfltText);
    this->setFont(*font);
    this->setCharacterSize(character_size);
    this->setPosition(sf::Vector2f(position.x + ((backdrop.getGlobalBounds().width - (character_size * character_limit)) / 2) - 1,
            position.y + ((this->backdrop.getGlobalBounds().height - character_size) / 2) - 7));

    // Update Class Variables
    this->limit = character_limit;
}



// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->setString(this->getString() + static_cast<char>(CharTyped));
    } else if (CharTyped == DELETE_KEY) {
        if (this->getString().toUtf8().size() > 0) {
            deleteLastChar();
        }
    } else if (CharTyped == ESCAPE_KEY) {

    }

    this->setString(this->getString() + "_");
}



// Function for the 'BACKSPACE' Key
void Textbox::deleteLastChar () {
    // Transfer each character except the last one into a new string
    string origText = this->getString();
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }

    // Replace old string with new string (last character has been deleted)
    this->setString(newText);
}



void Textbox::setLimit (unsigned character_limit) {
    this->limit = character_limit;
}



void Textbox::update (sf::Event input) {
    int CharType = input.text.unicode;
    if (CharType < 128) {
        if (this->getString().getSize() <= this->limit) {
                inputLogic(CharType);
        } else if (this->getString().getSize() > this->limit && CharType == DELETE_KEY) {
            deleteLastChar();
        }
    }
}



void Textbox::render (sf::RenderTarget& target) {
    target.draw(this->backdrop);
    target.draw(*this);
}

