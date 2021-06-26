#include "Sword.hpp"

void Sword::initVariables() 
{

}

void Sword::initComponents() 
{
    this->createHitboxComponent(this->sprite, 0.f, 0.f, 15.f, 45.f);
}

Sword::Sword( const float x, const float y, sf::Texture& texture_sheet) 
{
    this->setPosition( x, y );
    this->setTexture( texture_sheet );

    this->initComponents();
    this->createAnimationComponent( texture_sheet );
    this->animationComponent->addAnimation( "IDLE", 1.f, 0, 0, 0, 0, 15, 45 );

    
}

Sword::~Sword() 
{

}

void Sword::swing()
{
    this->sprite.setOrigin( 0.f, this->sprite.getGlobalBounds().height );

    while ( this->sprite.getRotation() < 200.f && this->sprite.getRotation() > 0.f )
    {
        this->sprite.rotate( 10.f );

    }
}

void Sword::update(const float& dt) 
{
    this->animationComponent->play("IDLE", dt);
    

    this->hitboxComponent->update();
}
