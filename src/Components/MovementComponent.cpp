#include "MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent() 
{
    
}

const float & MovementComponent::getMaxVelocity() const 
{
    return this->maxVelocity;
}

const sf::Vector2f & MovementComponent::getVelocity() const 
{
    return this->velocity;
}

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

const int MovementComponent::getDirection()
{
    return this->lastDirection;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) 
{
    // Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

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
