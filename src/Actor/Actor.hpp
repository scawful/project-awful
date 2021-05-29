#ifndef Actor_hpp
#define Actor_hpp

#include "../core.hpp"
#include "../Components/MovementComponent.hpp"

class Actor
{
private:
    // Initializer Functions
    void initVariables();

protected:
    sf::Sprite sprite;

    MovementComponent* movementComponent;
    
public:
    Actor();
    virtual ~Actor();

    // Components
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    
    // Setters
    void setTexture(sf::Texture& texture);
    virtual void setPosition(const float x, const float y);
        
    // Functions
    virtual void move(const float dir_x, const float dir_y, const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

#endif /* Actor_hpp */
