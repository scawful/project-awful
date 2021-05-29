#include "Player.hpp"

void Player::initVariables() 
{
    this->attacking = false;
}

void Player::initComponents() 
{
    // this calls the Actor member function to create a MovementComponent
    // the lifespan of that component is handled entirely by the parent
    this->createMovementComponent(350.f, 15.f, 5.f);
}

Player::Player(float x, float y, sf::Texture& texture_sheet) 
{
    this->setPosition(x, y);
    this->setTexture(texture_sheet);
    this->initComponents();
}

Player::~Player() 
{
    
}

void Player::update(const float& dt) 
{
    this->movementComponent->update(dt);

    // click to attack (?)
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->attacking = true;
    }
}
