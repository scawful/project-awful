#include "Actor.hpp"

void Actor::initVariables() 
{
    actorPositionX = 0;
    actorPositionY = 0;
    actorVelocityX = 0;
    actorVelocityY = 0;
}

Actor::Actor() 
{
    this->initVariables();
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
    actorPositionX = x;
    actorPositionY = y;
    this->sprite.setPosition(x, y);
}

void Actor::move(const float x, const float y, const float& dt)
{

}

void Actor::update(const float & dt) 
{        

}

void Actor::render(sf::RenderTarget& target) 
{
    target.draw(this->sprite);
}

