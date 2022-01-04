#ifndef Actor_hpp
#define Actor_hpp

#include "../core.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/MovementComponent.hpp"
#include "../Components/HitboxComponent.hpp"

class Actor
{
private:
    // Initializer Functions
    void initVariables();

protected:
    // sfml Sprite
    sf::Sprite sprite;

    // Components
    AnimationComponent* animationComponent;
    MovementComponent* movementComponent;
    HitboxComponent* hitboxComponent;

    // Actor Stats
    int level;
    float health, maxHealth, strength;
    
public:
    Actor();
    virtual ~Actor();

    // Components
    void createAnimatiomComponent(sf::Texture& texture_sheet);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createHitboxComponent(sf::Sprite& sprite,
                               float offset_x, float offset_y,
                               float width, float height);
    
    // Modifiers
    void setHealth( float health );
    void setTexture(sf::Texture& texture);
    void setPosition(const float x, const float y);

    // Accessors
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    float getHealth();
        
    // Functions
    virtual void move(const float dir_x, const float dir_y, const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

#endif /* Actor_hpp */
