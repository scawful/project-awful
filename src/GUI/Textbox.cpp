#include "Textbox.hpp"

/**
 * @brief Construct a new Textbox:: Textbox object
 * @author @jmielc2
 * 
 * @param position 
 * @param dimensions 
 * @param font 
 * @param character_size 
 * @param character_limit 
 * @param text_idle_color 
 * @param text_hover_color 
 * @param text_active_color 
 * @param idle_color 
 * @param hover_color 
 * @param active_color 
 * @param hasBorder 
 * @param dfltText 
 */
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
    this->setPosition(position.x + character_size / 2 - 1,
            position.y + ((dimensions.y - character_size) / 2) - 5);
    if (hasBorder) {
        this->setOutlineColor(sf::Color::Black);
        this->backdrop.setOutlineColor(sf::Color::Black);
        this->backdrop.setOutlineThickness(1);
    }

    // Update Private Variables
    this->assignColors(text_idle_color, text_hover_color, text_active_color, idle_color, hover_color, active_color);
}

/**
 * @brief Handle user input logic for typing in text
 * @author @jmielc2
 * 
 * @param charTyped 
 */
void Textbox::inputLogic (char charTyped) {
    if (charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != DELETE_KEY) {
        if (this->getString().getSize() < this->limit) {
            this->deleteLastChar();
            this->setString(this->getString() + charTyped + "_");
            if (this->getString() != "_") {
                this->isDefault = false;
            }
        }
        this->lastChar = charTyped;
    } else if (charTyped == DELETE_KEY) {
        if (this->getString().getSize() > 1) {
            this->deleteLastChar();
            this->deleteLastChar();
            this->setString(this->getString() + "_");
            if (this->getString() == "_") {
                this->isDefault = true;
            }
        } else if (this->getString().getSize() <= 1) {
            this->setString("_");
            this->isDefault = true;
        }
        this->lastChar = charTyped;
    } else if (charTyped == ESCAPE_KEY || charTyped == ENTER_KEY) {
        if (this->getString() == "_") {
            this->setString(this->dfltText);
            this->isDefault = true;
        } else {
            this->deleteLastChar();
        }
        this->isSelected = false;
    }
}

/**
 * @brief Delete the last character inputted 
 * @author @jmielc2
 * 
 */
void Textbox::deleteLastChar () {
    string origText = this->getString();
    string newText = "";
    for (int i = 0; i < origText.length() - 1; i++) {
        newText += origText.at(i);
    }
    this->setString(newText);
}

/**
 * @brief Set the character limit for the textbox
 * @author @jmielc2
 * 
 * @param character_limit 
 */
void Textbox::setLimit (unsigned character_limit) {
    this->limit = character_limit;
}

/**
 * @brief Get the inputted text as std::string object
 * @author @jmielc2
 * 
 * @return std::string 
 */
std::string Textbox::getInputText () {
    return this->getString();
}

/**
 * @brief Neutralize the textbox state
 * @author @jmielc2
 * 
 */
void Textbox::neutralize () {
    if (this->isSelected) {
        this->isSelected = false;
        if (this->getString() == "_") {
            this->isDefault = true;
        } else {
            this->deleteLastChar();
        }
    }
}

/**
 * @brief Cumulative update routine for the Textbox 
 * @author @jmielc2
 * 
 * @param mousePos 
 * @param event 
 */
void Textbox::update (const sf::Vector2f &mousePos, sf::Event &event) {
    // Set Textbox State
    textboxState = BTN_IDLE;
    if (this->backdrop.getGlobalBounds().contains(mousePos)) {
        textboxState = BTN_HOVER;
        if (this->isSelected) {
            textboxState = BTN_ACTIVE;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!this->isSelected) {
                if (this->isDefault) {
                    this->setString("_");
                } else {
                    this->setString(this->getString() + "_");
                }
            }
            textboxState = BTN_ACTIVE;
            this->isSelected = true;
        }
    } else {
        if (this->isSelected) {
            textboxState = BTN_ACTIVE;
        } else if (this->isDefault) {
            this->setString(this->dfltText);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            textboxState = BTN_IDLE;
            if (this->isSelected) {
                this->isSelected = false;
                if (this->isDefault) {
                    this->setString(this->dfltText);
                } else {
                    this->deleteLastChar();
                }
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
    
    if (event.type == sf::Event::TextEntered && this->isSelected) {
        if (this->keyTime < this->keyTimeMax && lastChar == event.text.unicode) {
            this->keyTime += 1.f;
        } else {
            this->inputLogic(event.text.unicode);
            this->keyTime = 0.f;
        }
    }
}

/**
 * @brief Cumulative render routien for the Textbox
 * @author @jmielc2
 * 
 * @param target 
 */
void Textbox::render (sf::RenderTarget& target) {
    if (this->checkBackdrop()) {
        target.draw(this->backdrop);
    }
    target.draw(*this);
}
