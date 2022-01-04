#ifndef TextBlock_hpp
#define TextBlock_hpp

#include "../core.hpp"

class TextBlock : public sf::Text 
{
private:
    // Backdrop Determiner
    bool hasBackdrop = false;
    
public:
    // Actual Backdrop
    sf::RectangleShape backdrop;

    // Constructors & Destructor
    TextBlock () {};
    TextBlock (string newText, sf::Font *newFont, const sf::Color newTextColor, int charSize, bool hasBorder);
    TextBlock (string newText, sf::Font *newFont, const sf::Color newTextColor, int charSize, bool hasBorder, 
            sf::Vector2f position);
    TextBlock (string newText, sf::Font *newFont, const sf::Color newTextColor, int charSize, bool hasBorder, 
            sf::Vector2f position, sf::Color backdropColor, sf::Vector2f dimensions);
    ~TextBlock () {}

    // Accessors
    const bool checkBackdrop () const;
    
    // Modifiers
    void setBackdrop (sf::Vector2f dimensions, sf::Color newColor, sf::Vector2f position, sf::Color border = sf::Color::Black, 
            float thickness = 0.f);
    void removeBackdrop () {this->hasBackdrop = false;}

    // Render routine 
    void render (sf::RenderTarget &window);
};

#endif