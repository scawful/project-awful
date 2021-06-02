#include "Textbox.hpp"

// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->setText(this->getText() + static_cast<char>(CharTyped));
    } else if (CharTyped == DELETE_KEY) {
        if (this->getText().length() > 0) {
            deleteLastChar();
        }
    }

    this->setText(this->getText() + "_");  // Adds indicator where user is typing
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
    this->setText(newText);
}

Textbox::Textbox (int size, bool selected) {
    this->setSize(size);
    this->isSelected = selected;
    if (selected) {
        this->setText("_");
    } else { 
        this->setText("");
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
        string origText = this->getText();
        string newText = "";
        for (int i = 0; i < origText.length() - 1; i++) {
            newText += origText.at(i);
        }
        this->setText(newText);
    } else {
        this->setText(this->getText() + "_");
    }
}

void Textbox::typedOn (sf::Event input) {
    if (isSelected) {
        int CharType = input.text.unicode;
        if (CharType < 128) {
            if (this->hasLimit) {
                if (this->getText().length() <= this->limit) {
                    inputLogic(CharType);
                } else if (this->getText().length() > this->limit && CharType == DELETE_KEY) {
                    deleteLastChar();
                }
            } else {
                inputLogic(CharType);
            }
        }
    }
}

