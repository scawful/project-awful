#ifndef DropDown_hpp
#define DropDown_hpp

#include "../core.hpp"
#include "Button.hpp"

class DropDown
{
private:
    float keytime;
    float keytimeMax;
    sf::Font& font;
    Button* activeElement;
    std::vector<Button*> list;
    bool showList;
    
public:
    DropDown(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string list[], unsigned numElements, const unsigned default_index = 0);
    ~DropDown();
    
    // Functions
    const bool getKeytime();
    void updateKeytime(const float& dt);
    void update(const sf::Vector2f& mousePos, const float& dt);
    void render(sf::RenderTarget& target);
};

#endif /* DropDown_hpp */