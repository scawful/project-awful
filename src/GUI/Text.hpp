#ifndef GUI_hpp
#define Gui_hpp

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
    TextBlock () {}
    TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, unsigned int charSize);
    TextBlock (sf::Vector2f position, string newText, sf::Font &newFont, const sf::Color newTextColor, unsigned int charSize, sf::Color backdropColor, sf::Vector2f dimensions);
    ~TextBlock() {}
    
    // Accessors
    const string getText() const;

    // Backdrop Operators
    void setCustomBackdrop (sf::Vector2f dimensions);
    void setBackdropColor (sf::Color newColor) {this->backdrop.setFillColor(newColor);}
    void removeBackdrop () {this->hasBackdrop = false;}

    // Functions
    void render(sf::RenderTarget &window);
};

#endif