#include "HitboxComponent.hpp"

/**
 * @brief Construct a new Hitbox Component:: Hitbox Component object
 * @author @scawful
 * 
 * @param sprite 
 * @param offset_x 
 * @param offset_y 
 * @param width 
 * @param height 
 */
HitboxComponent::HitboxComponent(sf::Sprite& sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
                        : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->hitbox.setPosition( this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y) ;
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Red);    
}

/**
 * @brief Destroy the Hitbox Component:: Hitbox Component object
 * 
 */
HitboxComponent::~HitboxComponent() 
{

}

/**
 * @brief Report if a given parameter rectangle intersects with the hitbox
 * @author @scawful
 * 
 * @param frect 
 * @return true 
 * @return false 
 */
bool HitboxComponent::checkIntersect(const sf::FloatRect& frect) 
{
    return this->hitbox.getGlobalBounds().intersects(frect);
}

/**
 * @brief Update the position of the hitbox
 * @author @scawful
 * 
 */
void HitboxComponent::update() 
{
    this->hitbox.setPosition( this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY );
}

/**
 * @brief Render the hitbox if it is meant to be visible
 * @author @scawful
 * 
 * @param target 
 */
void HitboxComponent::render(sf::RenderTarget& target) 
{
    target.draw(this->hitbox);
}
