#include "../core.hpp"
#include "Text.hpp"

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define DELETE_KEY 8

class Textbox : public TextBlock
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
    ~Textbox() {}
    void setLimit (bool TorF) {hasLimit = TorF;}
    void setLimit (bool TorF, int Limit);
    void setSelected (bool TorF);
    std::string retrieveInput() {return this->getString();}
    void drawTextbox (sf::RenderTarget &window) {
        
    }
    void typedOn (sf::Event input);
};