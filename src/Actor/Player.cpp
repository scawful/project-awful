#include "Player.hpp"

void Player::initVariables() 
{
    this->level = 1;
    this->maxHealth = 100;
    this->health = maxHealth;
    this->strength = 5;
    this->attacking = false;
}

void Player::initComponents() 
{
    // this calls the Actor member function to create a MovementComponent
    // the lifespan of that component is handled entirely by the parent
    this->createMovementComponent(250.f, 15.f, 9.f);
    this->createHitboxComponent(this->sprite, 0.f, 0.f, 62.f, 83.f);
}

Player::Player(float x, float y, sf::Texture& texture_sheet) 
{
    this->initVariables();
    this->setPosition(x, y);
    this->setTexture(texture_sheet);
    this->initComponents();
    this->createAnimatiomComponent(texture_sheet);
    
    //                                                                (x,y)
    //                                       key name       timer  start frames width height
    //                                                               frames 
    this->animationComponent->addAnimation( "IDLE",        11.f,   0, 0, 0, 0,  62,   83 );
    this->animationComponent->addAnimation( "IDLE_UP",     11.f,   0, 1, 0, 1,  62,   83 );
    this->animationComponent->addAnimation( "IDLE_SIDE",   11.f,   0, 2, 0, 2,  62,   83 );

    this->animationComponent->addAnimation( "WALK_DOWN",   10.f,   1, 0, 4, 0,  62,   83 );
    this->animationComponent->addAnimation( "WALK_UP",     10.f,   0, 1, 3, 1,  62,   83 );
    this->animationComponent->addAnimation( "WALK_SIDE",   10.f,   1, 2, 3, 2,  62,   83 );
    
    this->animationComponent->addAnimation( "ATTACK",      10.f,   1, 3, 3, 3,  62,   83 );

}

Player::~Player() 
{
    
}

void Player::update(const float& dt) 
{
    this->movementComponent->update(dt);

    // click to attack (?)
    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        this->attacking = true;
    }

    if ( this->attacking )
    {
        if ( this->animationComponent->play("ATTACK", dt, true) )
            this->attacking = false;
    }

    if ( this->movementComponent->getState(IDLE) )
    {
        switch ( this->movementComponent->getDirection() ) 
        {
            case MOVING_LEFT:
                this->animationComponent->play("IDLE_SIDE", dt);
                break;
            case MOVING_RIGHT:
                this->sprite.setScale(-1.f, 1.f);
                this->animationComponent->play("IDLE_SIDE", dt);
                break;
            case MOVING_UP:
                this->animationComponent->play("IDLE_UP", dt);
                break;
            case MOVING_DOWN:
                this->animationComponent->play("IDLE", dt);
                break;
            default:
                this->animationComponent->play("IDLE", dt);
                break;
        }
    }
    else if ( this->movementComponent->getState(MOVING_DOWN) )
    {
        this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
    else if ( this->movementComponent->getState(MOVING_UP) )
    {
        this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
    else if ( this->movementComponent->getState(MOVING_RIGHT) )
    {
        this->sprite.setOrigin(63.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);

        this->animationComponent->play("WALK_SIDE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if ( this->movementComponent->getState(MOVING_LEFT) )
    {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponent->play("WALK_SIDE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }

    this->hitboxComponent->update();

}
