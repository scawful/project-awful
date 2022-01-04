#ifndef HitboxComponent_hpp
#define HitboxComponent_hpp

#include "../core.hpp"

class HitboxComponent 
{
private:
    // Position values 
    float offsetX;
    float offsetY;

    // sfml Sprite 
    sf::Sprite& sprite;

    // sfml RectangleShape
    sf::RectangleShape hitbox;

public:
    HitboxComponent(sf::Sprite& sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    virtual ~HitboxComponent();
    
    // Functions
    bool checkIntersect(const sf::FloatRect& frect);
    
    // Update routine 
    void update();

    // Render routine
    void render(sf::RenderTarget& target);

};

#endif /* HitboxComponent_hpp */
