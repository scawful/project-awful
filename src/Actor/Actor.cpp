#include "Actor.hpp"

/**
 * @brief Initialize component variables
 * @author @scawful 
 * 
 */
void Actor::initVariables() 
{
    this->animationComponent = NULL;
    this->movementComponent = NULL;
    this->hitboxComponent = NULL;
}

/**
 * @brief Construct a new Actor:: Actor object
 * @author @scawful 
 * 
 */
Actor::Actor() 
{
    this->initVariables();
}

/**
 * @brief Destroy the Actor:: Actor object
 * @author @scawful
 * 
 */
Actor::~Actor() 
{
    delete this->movementComponent;
    delete this->hitboxComponent;
    delete this->animationComponent;
}

/**
 * @brief Create the AnimationComponent object with a given texture sheet
 * @author @scawful
 * 
 * @param texture_sheet 
 */
void Actor::createAnimatiomComponent(sf::Texture & texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

/**
 * @brief Create a MovementComponent object with the given maximum velocity, acceleration, and deceleration
 * @author @scawful 
 * 
 * @param maxVelocity 
 * @param acceleration 
 * @param deceleration 
 */
void Actor::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) 
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

/**
 * @brief Create a HitboxComponent object given the Actors sprite, position offset, and dimensions
 * @author @scawful
 * 
 * @param sprite 
 * @param offset_x 
 * @param offset_y 
 * @param width 
 * @param height 
 */
void Actor::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) 
{
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

/**
 * @brief Assign the actors health via parameter
 * @author @scawful 
 * 
 * @param health 
 */
void Actor::setHealth( float health )
{
    if ( this->health > this->maxHealth )
        this->health = maxHealth;
    else if ( this->health > 0 )
        this->health = health;
    else
        this->health = 1;
}

/**
 * @brief Assign the Actors sprite texture 
 * @author @scawful
 * 
 * @param texture 
 */
void Actor::setTexture(sf::Texture& texture) 
{
    this->sprite.setTexture(texture);
}

/**
 * @brief Assign the actors sprites position
 * @author @scawful
 * 
 * @param x 
 * @param y 
 */
void Actor::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

/**
 * @brief Retrieve the position of the actors sprite
 * @author @scawful
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Actor::getPosition()
{
    return sf::Vector2f( this->sprite.getPosition().x, this->sprite.getPosition().y );
}

/**
 * @brief Retrieve the dimensions of the actors texture rectangle
 * @author @scawful
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Actor::getSize()
{
    return sf::Vector2f( this->sprite.getTextureRect().width, this->sprite.getTextureRect().height );
}

/**
 * @brief Retrieve the actors health value
 * @author @scawful
 * 
 * @return float 
 */
float Actor::getHealth()
{
    return this->health;
}

/**
 * @brief Move the Actor in a direction via the MovementComponent
 * @author @scawful
 * 
 * @param dir_x 
 * @param dir_y 
 * @param dt 
 */
void Actor::move(const float dir_x, const float dir_y, const float& dt)
{
    if ( this->movementComponent ) 
    {
        this->movementComponent->move(dir_x, dir_y, dt); // sets velocity
    }
}

/**
 * @brief Update the actors state
 * @author @scawful
 * 
 * @param dt 
 */
void Actor::update(const float & dt) 
{        

}

/**
 * @brief Render the actors sprite and hitbox
 * @author @scawful
 * 
 * @param target 
 */
void Actor::render(sf::RenderTarget& target) 
{
    target.draw(this->sprite);

    if ( this->hitboxComponent )
            this->hitboxComponent->render(target);
}

