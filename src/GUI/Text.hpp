#include "../core.hpp"

class TextBlock : public sf::Text 
{
private:
    bool hasBackdrop = false;
    sf::RectangleShape backdrop;
    sf::Vector2f backdropDimensions;

public:
    TextBlock () {}
    TextBlock (string newText, sf::Font &newFont, int size);
    ~TextBlock() {}
    
    void setDefaultBackdrop (sf::Color color);
    void setCustomBackdrop (sf::Color color, sf::Vector2f dimensions);
    void setAdjustedBackdrop (sf::Color color, sf::Vector2f dimensions);
    void backdropColor (sf::Color newColor) {this->backdrop.setFillColor(newColor);}
    void removeBackdrop () {this->hasBackdrop = false;}
    void drawTextBlock(sf::RenderTarget &window);
};