#include "../core.hpp"
#include "Button.hpp"

#define ESCAPE_KEY 27
#define ENTER_KEY 13
#define DELETE_KEY 8

class Textbox : public Button 
{
private:
    bool hasLimit = false;
    int limit;

    void inputLogic (int CharTyped);
    void deleteLastChar ();

public:
    Textbox () {}
    Textbox (sf::Font &font, int size);
    ~Textbox() {}

    // Modifiers
    void setLimit (bool TorF, int Limit);

    // Functions
    void update (sf::Event input);
};