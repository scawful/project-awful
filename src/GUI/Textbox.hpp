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
};