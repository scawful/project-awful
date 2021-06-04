#include "../core.hpp"

class Text {
private:
    sf::Text textbox;
    std::ostringstream text;
    sf::Vector2f pos = {0, 0};
    bool hasBackdrop = false;
    sf::RectangleShape backdrop;

public:
    Text () {}
    Text (string newText, sf::Font newFont, int size, sf::Color &color, sf::Vector2f newPos);
    ~Text() {}
    
    void setText (string newText);
    std::string getText () {return this->text.str();}
    void setCharSize (int newSize) {this->textbox.setCharacterSize(newSize);}
    void setFont (sf::Font newFont) {this->textbox.setFont(newFont);}
    void setTextColor (sf::Color &newColor) {this->textbox.setColor(newColor);}
    void setPosition (sf::Vector2f newPos);
    void setBackdrop (sf::Color &color, sf::Vector2f dimensions);
    void setBackdropColor (sf::Color &newColor) {this->backdrop.setFillColor(newColor);}
    void removeBackdrop () {this->hasBackdrop = false;}
    void drawText (sf::RenderTarget &window);
};