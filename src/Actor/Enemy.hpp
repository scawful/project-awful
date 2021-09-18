#ifndef Enemy_hpp
#define Enemy_hpp

#include "Actor.hpp"
#include "../Components/HitboxComponent.hpp"

class Enemy :
    public Actor 
{
private:
    // Variables
    bool attacking;
    float damage;
        
    // Initializer Functions
    void initVariables();
    void initComponents();
public:
    Enemy(float x, float y, sf::Texture& texture_sheet, float damage);
    virtual ~Enemy();
        
    // Functions
    float getDamage();
    sf::Vector2f normalize(const sf::Vector2f& source);
    virtual void update(const float& dt);
};

#endif /* Enemy_hpp */
