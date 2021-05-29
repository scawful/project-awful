#ifndef Actor_hpp
#define Actor_hpp

#include "../core.hpp"

class Actor
{
private:
    // Initializer Functions
    void initVariables();

protected:
    sf::Sprite sprite;
    float actorPositionX, actorPositionY;
    float actorVelocityX, actorVelocityY;
    
public:
    Actor();
    virtual ~Actor();

    void setTexture(sf::Texture& texture);

    // Functions
    virtual void setPosition(const float x, const float y);
        
    // Functions
    virtual void move(const float x, const float y, const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

#endif /* Actor_hpp */
