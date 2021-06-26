#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "../core.hpp"

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent 
{
private:
    // Variables
    int lastDirection;
    sf::Sprite& sprite;

    float maxVelocity;    
    float acceleration;
    float deceleration;
    
    sf::Vector2f velocity;

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();
    
    // Accessors
    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;
    
    // Functions
    const bool getState(const short unsigned state);
    const int getDirection();
    
    void move(const float x, const float y, const float& dt);
    void update(const float& dt);
    
};

#endif /* MovementComponent_hpp */
