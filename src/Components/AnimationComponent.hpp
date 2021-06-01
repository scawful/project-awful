#ifndef AnimationComponent_hpp
#define AnimationComponent_hpp

#include "../core.hpp"

class AnimationComponent 
{
private:
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    
public:
    AnimationComponent( sf::Sprite& sprite, sf::Texture& texture_sheet );
    virtual ~AnimationComponent();
    
    // Accessors
    const bool& isDone( const std::string key );
    
    // Functions
    void addAnimation( const std::string key, float animation_timer,
                       int start_frame_x, int start_frame_y, int frames_x, int frames_y, 
                       int width, int height );
    
    const bool& play( const std::string key, const float& dt, const bool priority = false );
    const bool& play( const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false );

};

#endif /* AnimationComponent_hpp */
