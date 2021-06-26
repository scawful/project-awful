#ifndef Sword_hpp
#define Sword_hpp

#include "Ancilla.hpp"

class Sword : public Ancilla
{
private:
    bool active;

    void initVariables();
    void initComponents();

public:
    Sword(const float x, const float y, sf::Texture& texture_sheet);
    ~Sword();

    void swing();

    virtual void update(const float& dt);
};

#endif