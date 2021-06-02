#include "Enemy.hpp"

void Enemy::initVariables() 
{
    this->attacking = false;
}

void Enemy::initComponents() 
{
    // this calls the Actor member function to create a MovementComponent
    // the lifespan of that component is handled entirely by the parent
    this->createMovementComponent(250.f, 10.f, 7.f);
    this->createHitboxComponent(this->sprite, 0.f, 0.f, 80.f, 80.f);
}

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet) 
{
    this->setPosition(x, y);
    this->setTexture(texture_sheet);
    this->initComponents();
    this->createAnimatiomComponent(texture_sheet);
    
    this->animationComponent->addAnimation( "IDLE",       11.f,   0, 0, 0, 0,  80,   80 );


}

Enemy::~Enemy() 
{
    
}

sf::Vector2f Enemy::normalize(const sf::Vector2f& source)
{
    float length = sqrt( ( source.x * source.x ) + ( source.y * source.y ) );
    if ( length != 0 )
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

void Enemy::update(const float& dt) 
{
    this->movementComponent->update(dt);

    this->animationComponent->play("IDLE", dt);

    this->hitboxComponent->update();

}
