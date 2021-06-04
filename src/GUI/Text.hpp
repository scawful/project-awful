#include "../core.hpp"

class TextBlock : public sf::Text 
{
private:
    bool hasBackdrop = false;
    sf::RectangleShape backdrop;

public:
    TextBlock () {}
    TextBlock (string newText, sf::Font &newFont, int size);
    ~TextBlock() {}
    
    void setBackdrop (sf::Color color, sf::Vector2f dimensions);
    void BackdropColor (sf::Color newColor) {this->backdrop.setFillColor(newColor);}
    void removeBackdrop () {this->hasBackdrop = false;}
    void drawTextBlock (sf::RenderTarget &window);
};