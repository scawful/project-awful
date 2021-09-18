#ifndef HitboxComponent_hpp
#define HitboxComponent_hpp

#include "../core.hpp"

class HitboxComponent 
{
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    float offsetX;
    float offsetY;
    bool active;
public:
    HitboxComponent(sf::Sprite& sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    virtual ~HitboxComponent();
    
    // Functions
    bool checkIntersect(const sf::FloatRect& frect);
    void activate();
    void deactivate();
    bool isActive();
    void update();
    void render(sf::RenderTarget& target);
};

#endif /* HitboxComponent_hpp */
