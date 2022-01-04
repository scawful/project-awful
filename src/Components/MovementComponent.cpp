#include "MovementComponent.hpp"

/**
 * @brief Construct a new Movement Component:: Movement Component object
 * @author @scawful
 * 
 * @param sprite 
 * @param maxVelocity 
 * @param acceleration 
 * @param deceleration 
 */
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    this->maxVelocity = maxVelocity;
}

/**
 * @brief Destroy the Movement Component:: Movement Component object
 * @author @scawful
 * 
 */
MovementComponent::~MovementComponent() 
{
    
}

/**
 * @brief Retrieve the max velocity member variable 
 * @author @scawful
 * 
 * @return const float& 
 */
const float & MovementComponent::getMaxVelocity() const 
{
    return this->maxVelocity;
}

/**
 * @brief Retrieve the currente velocity member variable
 * @author @scawful
 * 
 * @return const sf::Vector2f& 
 */
const sf::Vector2f & MovementComponent::getVelocity() const 
{
    return this->velocity;
}

/**
 * @brief Retrieve the current state of the MovementComponent
 * @author @scawful
 * 
 * @param state 
 * @return true 
 * @return false 
 */
const bool MovementComponent::getState(const short unsigned state) 
{
    switch (state) 
    {
        case IDLE:
            if ( this->velocity.x == 0.f && this->velocity.y == 0.f )
                return true;
            break;
        case MOVING:
            if ( this->velocity.x != 0.f || this->velocity.y != 0.f )
                return true;
            break;
        case MOVING_LEFT:
            this->lastDirection = MOVING_LEFT;
            if ( this->velocity.x < 0.f )
                return true;
            break;
        case MOVING_RIGHT:
            this->lastDirection = MOVING_RIGHT;
            if ( this->velocity.x > 0.f )
                return true;
            break;
        case MOVING_UP:
            this->lastDirection = MOVING_UP;
            if ( this->velocity.y < 0.f )
                return true;
            break;
        case MOVING_DOWN:
            this->lastDirection = MOVING_DOWN;
            if ( this->velocity.y > 0.f )
                return true;
            break;
    }
    
    return false;
}

/**
 * @brief Retrieve the direction of the MovementComponent as reported by getState
 * @author @scawful
 * 
 * @return const int 
 */
const int MovementComponent::getDirection()
{
    return this->lastDirection;
}

/**
 * @brief Shift the direction of the object using acceleration added to the current velocity of the object
 * @author @scawful
 * 
 * @param dir_x 
 * @param dir_y 
 * @param dt 
 */
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) 
{
    // Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

/**
 * @brief Update the object 
 *        Decelerate the objects velocity if no longer in motion or moving in another direction
 * @author @scawful
 * 
 * @param dt 
 */
void MovementComponent::update(const float& dt) 
{
    // Deceleration
    if (this->velocity.x > 0.f)
    { // check right movement positive
        // Max velocity check x positive
        if ( this->velocity.x > this->maxVelocity )
            this->velocity.x = this->maxVelocity;
        
        // Deceleration x positive
        this->velocity.x -= deceleration;
        if ( this->velocity.x < 0.f )
            this->velocity.x = 0.f;
        
    }
    else if (this->velocity.x < 0.f) // check left movement negative
    { 
        // max velocity check x negative
        if ( this->velocity.x < -this->maxVelocity )
            this->velocity.x = -this->maxVelocity;
        
        // deceleration x negative
        this->velocity.x += deceleration;
        if ( this->velocity.x > 0.f )
              this->velocity.x = 0.f;
    }
    
    if (this->velocity.y > 0.f) 
    {
        // Max velocity check y positive
        if ( this->velocity.y > this->maxVelocity )
            this->velocity.y = this->maxVelocity;
        
        // Deceleration y positive
        this->velocity.y -= deceleration;
        if ( this->velocity.y < 0.f )
            this->velocity.y = 0.f;
    }
    else if (this->velocity.y < 0.f)
    {
        // max velocity check y negative
        if ( this->velocity.y < -this->maxVelocity )
            this->velocity.y = -this->maxVelocity;
        
        // deceleration y negative
        this->velocity.y += deceleration;
        if ( this->velocity.y > 0.f )
              this->velocity.y = 0.f;
    }
    
    // Final move
    this->sprite.move(this->velocity * dt);
    
}
