#include "../core.hpp"
#include "Text.hpp"

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define DELETE_KEY 8

class Textbox : public Text 
{
private:
    bool isSelected = false;
    bool hasLimit = false;
    int limit;

    void inputLogic (int CharTyped);
    void deleteLastChar ();

public:
    Textbox () {}
    Textbox (int size, bool selected);
    ~Textbox();
    void setLimit (bool TorF) {hasLimit = TorF;}
    void setLimit (bool TorF, int Limit);
    void setSelected (bool TorF);
    std::string retrieveInput() {return this->getText();}
    void drawTextbox (sf::RenderWindow &window) {
        //cout << "Drawing NOW" << endl;
        this->drawText(window);
    }
    void typedOn (sf::Event input);
};