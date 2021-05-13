#include "Actor.hpp"

void Actor::initVariables() 
{
    this->attacking = false;
}

Actor::Actor(float x, float y, sf::Texture& texture_sheet) 
{
    this->initVariables();
    this->setPosition(x, y);
}

Actor::~Actor() 
{
    
}

void Actor::setTexture(sf::Texture& texture) 
{
    this->sprite.setTexture(texture);
}

void Actor::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}


void Actor::update(const float & dt) 
{        

}

void Actor::render(sf::RenderTarget& target) 
{
    target.draw(this->sprite);
}

