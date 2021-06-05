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
    
    void setBackdrop (sf::Color color);
    void setCustomBackdropDims (sf::Vector2f dimensions) {this->backdrop.setSize(dimensions);}
    void adjustBackdropDims (sf::Vector2f dimensions);
    void BackdropColor (sf::Color newColor) {this->backdrop.setFillColor(newColor);}
    void outputDimensions () {cout << backdropDimensions.x << ", " << backdropDimensions.y;}
    void removeBackdrop () {this->hasBackdrop = false;}
    void drawTextBlock(sf::RenderTarget &window);
};