#include "Textbox.hpp"

// Logic for when a person types something (exceptions are: 'ESC', 'BACKSPACE', and 'ENTER' Keys)
void Textbox::inputLogic (int CharTyped) {
    if (CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        text << static_cast<char>(CharTyped);
    } else if (CharTyped == DELETE_KEY) {
        if (text.str().length() > 0) {
            deleteLastChar();
        }
    } else if (CharTyped == ESCAPE_KEY) {
        // TODO
    } else if (CharTyped == ENTER_KEY) {
        // TODO
    }
}

// Function for the 'BACKSPACE' Key
void Textbox::deleteLastChar () {
    // Transfer each character except the last one into a new string
    string origText = text.str();
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }
    
    // Replace old string with new string (last character has been deleted)
    text.str() = "";
    text << newText;  // Use the '<<' because text is sstream type not string type

    // Update Textbox object
    textbox.setString(text.str());
}

Textbox::Textbox (int size, sf::Color color, bool selected) {
    this->textbox.setCharacterSize(size);
    this->textbox.setColor(color);
    this->isSelected = selected;
}

Textbox::~Textbox () {

}