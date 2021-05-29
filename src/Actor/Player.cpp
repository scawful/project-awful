#include "Player.hpp"

void Player::initVariables() 
{
    this->attacking = false;
}

void Player::initComponents() 
{
    
}

Player::Player(float x, float y, sf::Texture& texture_sheet) 
{
    this->setPosition(x, y);
    this->setTexture(texture_sheet);
}

Player::~Player() 
{
    
}

void Player::move(const float x, const float y, const float& dt)
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
    actorPositionY += actorVelocityY;

    //If the dot went too far up or down
    if( ( actorPositionY < 0 ) || ( actorPositionY + 20 > SCREEN_HEIGHT ) )
    {
        //Move back
        actorPositionY -= actorVelocityY;
    }
}

void Player::update(const float& dt) 
{
    this->sprite.setPosition( actorPositionX, actorPositionY );
}
