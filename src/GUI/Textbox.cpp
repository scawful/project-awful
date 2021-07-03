#include "Textbox.hpp"

// Constructor
Textbox::Textbox (sf::Font &font, int size) {
    
}

// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->setString(this->getText() + static_cast<char>(CharTyped));
    } else if (CharTyped == DELETE_KEY) {
        if (this->getText().size() > 0) {
            deleteLastChar();
        }
    } else if (CharTyped == ESCAPE_KEY) {

    }

    this->setString(this->getText() + "_");
}


// Function for the 'BACKSPACE' Key
void Textbox::deleteLastChar () {
    // Transfer each character except the last one into a new string
    string origText = this->getText();
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }

    // Replace old string with new string (last character has been deleted)
    this->setString(newText);
}


void Textbox::setLimit (bool TorF, int Limit) {
    this->hasLimit = TorF;
    if (this->hasLimit) {
        this->limit = Limit;
    }
}


void Textbox::update (sf::Event input) {
    int CharType = input.text.unicode;
    if (CharType < 128) {
        if (this->hasLimit) {
            if (this->getString().getSize() <= this->limit) {
                inputLogic(CharType);
            } else if (this->getString().getSize() > this->limit && CharType == DELETE_KEY) {
                deleteLastChar();
            }
        } else {
            inputLogic(CharType);
        }
    }
}

