#include "Textbox.hpp"

// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->text << static_cast<char>(CharTyped);
    } else if (CharTyped == DELETE_KEY) {
        if (this->text.str().length() > 0) {
            deleteLastChar();
        }
    }

    this->textbox.setString(text.str() + "_");  // Adds indicator where user is typing
}

// Function for the 'BACKSPACE' Key
void Textbox::deleteLastChar () {
    // Transfer each character except the last one into a new string
    string origText = this->text.str();
    cout << "ORIG: " << origText << endl;
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }
    cout << "NEW: " << newText << endl;

    // Replace old string with new string (last character has been deleted)
    this->text << newText;
}

Textbox::Textbox (int size, sf::Color color, bool selected) {
    this->textbox.setCharacterSize(size);
    this->textbox.setColor(color);
    this->isSelected = selected;
    if (selected) {
        textbox.setString("_");
    } else { 
        textbox.setString("");
    }
}

Textbox::~Textbox () {

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
        string origText = this->text.str();
        string newText = "";
        for (int i = 0; i < origText.length() - 1; i++) {
            newText += origText.at(i);
        }
        this->textbox.setString(newText);
    } else {
        this->textbox.setString(this->text.str() + "_");
    }
}

void Textbox::typedOn (sf::Event input) {
    if (isSelected) {
        int CharType = input.text.unicode;
        if (CharType < 128) {
            if (this->hasLimit) {
                if (text.str().length() <= this->limit) {
                    inputLogic(CharType);
                } else if (text.str().length() > this->limit && CharType == DELETE_KEY) {
                    deleteLastChar();
                }
            }else {
                inputLogic(CharType);
            }
        }
    }
}

