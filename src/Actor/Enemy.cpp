#include "Enemy.hpp"

void Enemy::initVariables() 
{
    this->attacking = false;
}

void Enemy::initComponents() 
{
    // this calls the Actor member function to create a MovementComponent
    // the lifespan of that component is handled entirely by the parent
    this->createMovementComponent(200.f, 10.f, 7.f);
    this->createHitboxComponent(this->sprite, 0.f, 0.f, 80.f, 80.f);
}

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, float damage) 
{
    this->setPosition(x, y);
    this->setTexture(texture_sheet);
    this->damage = damage;
    this->initComponents();
    this->createAnimatiomComponent(texture_sheet);
    this->animationComponent->addAnimation( "IDLE", 11.f, 0, 0, 0, 0, 80, 80 );
}

Enemy::~Enemy() 
{

}

float Enemy::getDamage()
{
    return this->damage;
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

    if ( this->movementComponent->getState(MOVING_RIGHT) )
    {
        this->sprite.setOrigin(80.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);

        this->animationComponent->play("IDLE", dt);
    }
    else if ( this->movementComponent->getState(MOVING_LEFT) )
    {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponent->play("IDLE", dt);
    }

    this->hitboxComponent->update();
}
