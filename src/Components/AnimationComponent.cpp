#include "AnimationComponent.hpp"

/**
 * @brief Construct a new Animation Component:: Animation Component object
 * @author @scawful
 * 
 * @param sprite 
 * @param texture_sheet 
 */
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) 
    : sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{
    
}

/**
 * @brief Destroy the Animation Component:: Animation Component object
 * @author @scawful
 * 
 */
AnimationComponent::~AnimationComponent() 
{
    for ( auto &i : this->animations ) 
    {
        delete i.second;
    }
}

// Accessors

/**
 * @brief Report if the animation for the parameter is finished executing
 * @author @scawful
 * 
 * @param key 
 * @return true 
 * @return false 
 */
const bool & AnimationComponent::isDone(const std::string key) 
{
    return this->animations[key]->isDone();
}

/**
 * @brief Add a new animation with the given parameters to the component
 * @author @scawful
 * 
 * @param key 
 * @param animation_timer 
 * @param start_frame_x 
 * @param start_frame_y 
 * @param frames_x 
 * @param frames_y 
 * @param width 
 * @param height 
 */
void AnimationComponent::addAnimation( const std::string key, float animation_timer,
                                       int start_frame_x, int start_frame_y, int frames_x, int frames_y, 
                                       int width, int height )
{
    this->animations[key] = new Animation( this->sprite, this->textureSheet, animation_timer,
                                           start_frame_x, start_frame_y, frames_x, frames_y, 
                                           width, height );
}

/**
 * @brief Play an animation based on the requested key and if applicable priority status
 * @author @scawful
 * 
 * @param key 
 * @param dt 
 * @param priority 
 * @return true 
 * @return false 
 */
const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
    if ( priority )
    {
        this->priorityAnimation = this->animations[key];
    }
    
    // priority animations play on top of any existing animations
    // they are discarded upon completion
    if ( this->priorityAnimation )
    {
        if ( this->priorityAnimation == this->animations[key] )
        {
            if ( this->lastAnimation != this->animations[key] )
            {
                if ( this->lastAnimation == NULL ) {
                    this->lastAnimation = this->animations[key];
                } else {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }
            
            // if priority animation is done, remove it
            if (this->animations[key]->play(dt))
            {
                this->priorityAnimation = NULL;
            }
        }
    }
    else
    {
        if ( priority )
        {
            this->priorityAnimation = this->animations[key];
        }
        
        if ( this->lastAnimation != this->animations[key] )
        {
            if ( this->lastAnimation == NULL ) {
                this->lastAnimation = this->animations[key];
            } else {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }

        this->animations[key]->play(dt);
    }

    return this->animations[key]->isDone();
}

/**
 * @brief Overloaded play with added modifier for speed 
 * @author @scawful
 * 
 * @param key 
 * @param dt 
 * @param modifier 
 * @param modifier_max 
 * @param priority 
 * @return true 
 * @return false 
 */
const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
    if (priority)
    {
        this->priorityAnimation = this->animations[key];
    }
    
    if ( this->priorityAnimation )
    {
        if ( this->priorityAnimation == this->animations[key] )
        {
            if ( this->lastAnimation != this->animations[key] )
            {
                if ( this->lastAnimation == NULL ) {
                    this->lastAnimation = this->animations[key];
                } else {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }
            
            // if priority animation is done, remove it
            if ( this->animations[key]->play(dt) )
            {
                this->priorityAnimation = NULL;
            }
        }
    }
    else
    {
        if ( priority )
        {
            this->priorityAnimation = this->animations[key];
        }
        
        if ( this->lastAnimation != this->animations[key] )
        {
            if ( this->lastAnimation == NULL ) {
                this->lastAnimation = this->animations[key];
            } else {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }
        
        this->animations[key]->play(dt, abs(modifier / modifier_max));
    }

    return this->animations[key]->isDone();
}

