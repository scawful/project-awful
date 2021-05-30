#include "Textbox.hpp"

// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        this->text << static_cast<char>(CharTyped);
    } else if (CharTyped == DELETE_KEY) {
        if (this->text.str().length() > 0) {
            deleteLastChar();
        }
    } else if (CharTyped == ESCAPE_KEY) {
        // TODO
    } else if (CharTyped == ENTER_KEY) {
        // TODO
    }

    this->textbox.setString(text.str() + "_");  // Adds indicator where user is typing
}

// Function for the 'BACKSPACE' Key
void Textbox::deleteLastChar () {
    // Transfer each character except the last one into a new string
    string origText = this->text.str();
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }
    
    // Replace old string with new string (last character has been deleted)
    this->text.str() = "";
    this->text << newText;  // Use the '<<' because 'text' is sstream type not string type

    // Update Textbox object
    this->textbox.setString(this->text.str());
}

Textbox::Textbox (int size, sf::Color color, bool selected) {
    this->textbox.setCharacterSize(size);
    this->textbox.setColor(color);
    this->isSelected = selected;
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
        textbox.setString(newText);
    } else {
        textbox.setString(this->text.str() + "_");
    }
}