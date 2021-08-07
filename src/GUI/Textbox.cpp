#include "Textbox.hpp"

// Constructor
Textbox::Textbox (sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, unsigned character_size, unsigned character_limit,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color, bool hasBorder, string dfltText = "")
            : limit(character_limit), isSelected(false), dfltText(dfltText) {
    
    this->textboxState = BTN_IDLE;
    
    this->setBackdrop(sf::Vector2f(dimensions.x, dimensions.y), idle_color, sf::Vector2f(position.x, position.y), active_color, 1);
    this->setFont(*font);
    this->setString(dfltText);
    this->setFillColor(text_idle_color);
    this->setCharacterSize(character_size);
    this->setPosition(position.x + ((dimensions.x - this->getGlobalBounds().width) / 2 - 1),
            position.y + ((dimensions.y - character_size) / 2) - 5);
    if (hasBorder) {
        this->setOutlineColor(sf::Color::Black);
        this->backdrop.setOutlineColor(sf::Color::Black);
        this->backdrop.setOutlineThickness(1);
    }

    // Update Private Variables
    this->assignColors(text_idle_color, text_hover_color, text_active_color, idle_color, hover_color, active_color);
}


void Textbox::inputLogic (char charTyped) {
    if (charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != DELETE_KEY) {
        this->setString(this->getString() + charTyped);
    } else if (charTyped == DELETE_KEY) {
        if (this->getString().toUtf8().size() > 0) {
            deleteLastChar();
        }
    } else if (charTyped == ESCAPE_KEY || charTyped == ENTER_KEY) {
        if (this->getString().toUtf8().size() > 0) {
            deleteLastChar();
            this->isSelected = false;
        }
    }

    this->setString(this->getString() + "_");
}


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


std::string Textbox::getInputText () {
    return this->getString();
}


void Textbox::updateInput (sf::Event &event) {
    this->inputLogic(event.text.unicode);
}


void Textbox::update (const sf::Vector2f &mousePos, sf::Event &event) {
    // Set Textbox State
    textboxState = BTN_IDLE;
    if (this->backdrop.getGlobalBounds().contains(mousePos)) {
        textboxState = BTN_HOVER;
        if (this->isSelected) {
            textboxState = BTN_ACTIVE;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            textboxState = BTN_ACTIVE;
            this->isSelected = true;
            if (this->isDefault) {
                this->setString("_");
            }
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                continue;
            }
        }
    } else {
        if (this->isSelected) {
            textboxState = BTN_ACTIVE;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            textboxState = BTN_IDLE;
            this->isSelected = false;
            if (this->isDefault) {
                this->setString(this->dfltText);
            }
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                continue;
            }
        }
    }

    // Update Textbox Color
    vector <sf::Color> colors = this->getStateColors(textboxState);
    switch (textboxState) {
        case BTN_IDLE:
            this->setFillColor(colors[0]);
            this->backdrop.setFillColor(colors[1]);
            this->backdrop.setOutlineColor(colors[0]);
            break;
        case BTN_HOVER:
            this->setFillColor(colors[0]);
            this->backdrop.setFillColor(colors[1]);
            this->backdrop.setOutlineColor(colors[0]);
            break;
        case BTN_ACTIVE:
            this->setFillColor(colors[0]);
            this->backdrop.setFillColor(colors[1]);
            this->backdrop.setOutlineColor(colors[0]);
            break;
    }
    
    if (event.type == sf::Event::TextEntered) {
        cout << "Key has been pressed" << endl;
        if (this->isSelected) {
            this->updateInput(event);
        }
    }
}


void Textbox::render (sf::RenderTarget& target) {
    if (this->checkBackdrop()) {
        target.draw(this->backdrop);
    }
    target.draw(*this);
}
