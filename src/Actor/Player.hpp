#ifndef Player_hpp
#define Player_hpp

#include "Actor.hpp"

class Player :
    public Actor 
{
private:
    // Variables
    bool attacking;
        
    // Initializer Functions
    void initVariables();
    void initComponents();
        
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();
        
    // Functions
    virtual void update(const float& dt);
};

#endif /* Player_hpp */
