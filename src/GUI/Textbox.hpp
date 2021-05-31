#include "../core.hpp"

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define DELETE_KEY 8

class Textbox {
private:
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;

    void inputLogic (int CharTyped);
    void deleteLastChar ();

public:
    Textbox () {}
    Textbox (int size, sf::Color color, bool selected);
    ~Textbox();
    void setFont (sf::Font &font) {textbox.setFont(font);}
    void setSize (int size) {textbox.setCharacterSize(size);}
    void setPosition (sf::Vector2f pos) {textbox.setPosition(pos);}
    void setLimit (bool TorF) {hasLimit = TorF;}
    void setLimit (bool TorF, int Limit);
    void setSelected (bool TorF);
    std::string getText() {return text.str();}
    void drawTo (sf::RenderWindow &window) {window.draw(textbox);}
    void typedOn (sf::Event input);
};