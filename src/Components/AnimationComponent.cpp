#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) :sprite(sprite), textureSheet(texture_sheet)
{
    
}

AnimationComponent::~AnimationComponent() 
{

}

// Accessors
const bool & AnimationComponent::isDone(const std::string key) 
{

}

void AnimationComponent::addAnimation( const std::string key, float animation_timer,
                                       int start_frame_x, int start_frame_y, int frames_x, int frames_y, 
                                       int width, int height )
{

}

const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{

}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{

}

