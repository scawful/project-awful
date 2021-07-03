#ifndef TextBlock_hpp
#define TextBlock_hpp

#include "../core.hpp"

class TextBlock : public sf::Text 
{
private:
    // Text
    sf::Font font;
    sf::Color textColor;

    // Backdrop
    bool hasBackdrop = false;
    sf::RectangleShape backdrop;
    sf::Color backdropColor;
    sf::Vector2f backdropDimensions;

public:
    TextBlock() {};
    TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, int charSize);
    TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, int charSize, sf::Color backdropColor, sf::Vector2f dimensions);
    ~TextBlock() {}
    
    // Accessors
    const string getText() const;

    // Modifiers
    void setText(const string newText);
    void setTextColor(sf::Color newColor);
    void setBackdrop (sf::Vector2f dimensions, sf::Color newColor, sf::Vector2f position);
    void setBackdropColor (sf::Color newColor);
    void removeBackdrop () {this->hasBackdrop = false;}

    // Functions
    void render(sf::RenderTarget &window);
};

#endif