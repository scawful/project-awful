#ifndef Textbox_hpp
#define Textbox_hpp

#include "../core.hpp"
#include "Button.hpp"

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define DELETE_KEY 8

class Textbox
{
private:
    unsigned int limit;
    float keytime;
    float keytimeMax;
    Button* box;
    bool isSelected;

    void inputLogic (int CharTyped);
    void deleteLastChar ();

public:
    Textbox () {}
    Textbox (sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, unsigned character_size, unsigned character_limit,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color, bool hasBorder, string dfltText);
    ~Textbox() {}

    // Modifiers
    void setLimit (unsigned character_limit);

    // Functions
    const bool getKeytime();
    void updateKeytime(const float& dt);
    void update (const sf::Vector2f &mousePos, const float& dt);
    void render (sf::RenderTarget& target);
};

#endif