#include "Actor.hpp"

void Actor::initVariables() 
{
    this->animationComponent = NULL;
    this->movementComponent = NULL;
    this->hitboxComponent = NULL;
}

Actor::Actor() 
{
    this->initVariables();
}

Actor::~Actor() 
{
    delete this->movementComponent;
    delete this->hitboxComponent;
    delete this->animationComponent;
}

void Actor::createAnimatiomComponent(sf::Texture & texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}


void Actor::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) 
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Actor::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) 
{
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Actor::setTexture(sf::Texture& texture) 
{
    this->sprite.setTexture(texture);
}

void Actor::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

sf::Vector2f Actor::getPosition()
{
    return sf::Vector2f( this->sprite.getPosition().x, this->sprite.getPosition().y );
}

sf::Vector2f Actor::getSize()
{
    return sf::Vector2f( this->sprite.getTextureRect().width, this->sprite.getTextureRect().height );
}

void Actor::move(const float dir_x, const float dir_y, const float& dt)
{
    if ( this->movementComponent ) 
    {
        this->movementComponent->move(dir_x, dir_y, dt); // sets velocity
    }
}

void Actor::update(const float & dt) 
{        

}

void Actor::render(sf::RenderTarget& target) 
{
    target.draw(this->sprite);

    if ( this->hitboxComponent )
            this->hitboxComponent->render(target);
}

