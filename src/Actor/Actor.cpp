#include "Actor.hpp"

void Actor::initVariables() 
{
    this->attacking = false;
    actorPositionX = 0;
    actorPositionY = 0;
    actorVelocityX = 0;
    actorVelocityY = 0;
}

Actor::Actor(float x, float y, sf::Texture& texture_sheet) 
{
    this->initVariables();
    this->setPosition(x, y);
    this->setTexture(texture_sheet);
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
    actorVelocityX = x;
    actorVelocityY = y;

    //Move the dot left or right
    actorPositionX += actorVelocityX;

    //If the dot went too far to the left or right
    if( ( actorPositionX < 0 ) || ( actorPositionX + 20 > SCREEN_WIDTH ) )
    {
        //Move back
        actorPositionX -= actorVelocityX;
    }

    //Move the dot up or down
    actorVelocityY += actorVelocityY;

    //If the dot went too far up or down
    if( ( actorVelocityY < 0 ) || ( actorVelocityY + 20 > SCREEN_HEIGHT ) )
    {
        //Move back
        actorVelocityY -= actorVelocityY;
    }
}

void Actor::update(const float & dt) 
{        


    this->sprite.setPosition( actorPositionX, actorPositionY );
}

void Actor::render(sf::RenderTarget& target) 
{
    target.draw(this->sprite);
}

