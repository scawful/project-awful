#include "Ancilla.hpp"


void Ancilla::initVariables() 
{
    this->active = false;
    this->animationComponent = NULL;
    this->hitboxComponent = NULL;
}

Ancilla::Ancilla()
{
    this->initVariables();
}

Ancilla::~Ancilla()
{
    delete this->hitboxComponent;
    delete this->animationComponent;
}

void Ancilla::createAnimationComponent(sf::Texture & texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Ancilla::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) 
{
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Ancilla::setTexture(sf::Texture& texture) 
{
    this->sprite.setTexture(texture);
}

void Ancilla::setPosition(const float x, const float y)
{
    this->sprite.setPosition( x, y );
}

void Ancilla::activate()
{
    this->active = true;
}

void Ancilla::deactivate()
{
    this->active = false;
}

void Ancilla::move(const float x, const float y, const float& dt)
{
    this->setPosition( x, y );
}

void Ancilla::update(const float & dt) 
{        

}

void Ancilla::render(sf::RenderTarget& target) 
{
    target.draw( this->sprite );

    if ( this->hitboxComponent )
            this->hitboxComponent->render(target);
}

