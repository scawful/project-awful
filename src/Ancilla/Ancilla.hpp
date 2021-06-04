#ifndef Ancilla_hpp
#define Ancilla_hpp

#include "../core.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/HitboxComponent.hpp"

class Ancilla
{
private:
    bool active;
    void initVariables();

protected:
    sf::Sprite sprite;

    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;

public:
    Ancilla();
    virtual ~Ancilla();

    // Components
    void createAnimationComponent(sf::Texture& texture_sheet);
    void createHitboxComponent(sf::Sprite& sprite,
                               float offset_x, float offset_y,
                               float width, float height);

    void setTexture(sf::Texture& texture);
    void setPosition(const float x, const float y);

    // Functions
    virtual void activate();
    virtual void deactivate();

    virtual void move(const float x, const float y, const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

#endif