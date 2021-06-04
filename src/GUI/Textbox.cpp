#include "Textbox.hpp"

// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->setString(this->getString() + static_cast<char>(CharTyped));
    } else if (CharTyped == DELETE_KEY) {
        if (this->getString().getSize() > 0) {
            deleteLastChar();
        }
    }

    this->setString(this->getString() + "_");  // Adds indicator where user is typing
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

Textbox::Textbox (int size, bool selected) {
    this->setCharacterSize(size);
    this->isSelected = selected;
    if (selected) {
        this->setString("_");
    } else { 
        this->setString("");
    }
}

void Textbox::setLimit (bool TorF, int Lim) {
    this->hasLimit = TorF;
    if (this->hasLimit) {
        this->limit = Lim;
    }
}

void Textbox::setSelected (bool TorF) {
    this->isSelected = TorF;
    if (!TorF) {
        string origText = this->getString();
        string newText = "";
        for (int i = 0; i < origText.length() - 1; i++) {
            newText += origText.at(i);
        }
        this->setString(newText);
    } else {
        this->setString(this->getString() + "_");
    }
}

void Textbox::typedOn (sf::Event input) {
    if (isSelected) {
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
}

