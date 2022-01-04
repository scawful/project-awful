#ifndef Button_hpp
#define Button_hpp

#include "../core.hpp"
#include "Text.hpp"

enum button { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button : public TextBlock
{
private:    
    // current state of the button based on the enum
    short unsigned buttonState;

    // fun colors for animation
    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;
    
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    
public:
    Button() {}
    Button( sf::Vector2f position, sf::Vector2f dimensions,
            sf::Font* font, std::string text, unsigned character_size, bool hasBorder, 
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
    ~Button();
    
    // Accessors
    const bool isPressed() const;
    vector <sf::Color> getStateColors(int state);

    // Modifiers
    void assignColors (sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color);

    // Update routine 
    void update(const sf::Vector2f& mousePos);

    // Render routine 
    void render(sf::RenderTarget& target);
};

#endif