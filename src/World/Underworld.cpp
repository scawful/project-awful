#include "Underworld.hpp"

void Underworld::initTextures() 
{
    
}

void Underworld::initFonts()
{
    this->gameFont.loadFromFile("../assets/ARCADECLASSIC.TTF");
}

void Underworld::initPlayers()
{
    this->playerSize = this->player->getSize();
    this->playerPosition = this->player->getPosition();
}

Underworld::Underworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef ) : World( playerRef, textureRef )
{
    this->initFonts();
    this->initPlayers();
    this->dungeonGenerator = new DungeonGenerator( 1 );

    // @scawful: commenting out debug lines for the master branch 
    // cout << "Underworld created" << endl;
}

Underworld::~Underworld() 
{
    delete this->dungeonGenerator;
    dungeonGenerator = NULL;

    // @scawful: commenting out debug lines for the master branch 
    // cout << "Underworld destroyed" << endl;
}

void Underworld::updateInput(const float& dt)
{
    // dynamically fetch keyboard input in real time to move the player 
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
        this->player->move(-1.f, 0.f, dt);

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
        this->player->move(1.f, 0.f, dt);

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
        this->player->move(0.f, -1.f, dt);

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
        this->player->move(0.f, 1.f, dt);
}

void Underworld::update(const float& dt) 
{
    playerPosition = this->player->getPosition();
    this->player->update(dt);

    this->updateInput(dt);
}

void Underworld::render(sf::RenderTarget &target) 
{
    // target.clear( sf::Color::Red );
    
    // the camera of the game, centered on the players position
    // viewports use the center rather than the top, left coordinates like the player
    // to compensate for a true center, we divide the players size in half and add that to the view coordinates
    sf::View dungeonView( sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
    sf::Vector2f trueCenter( this->player->getPosition() );
    trueCenter.x += playerSize.x / 2;
    trueCenter.y += playerSize.y / 2;
    dungeonView.setCenter( trueCenter );
    target.setView(dungeonView);

    this->dungeonGenerator->render(target);
    this->player->render(target);

    // ====================== //

    sf::View guiView( sf::FloatRect(  0.75f, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
    target.setView(guiView);

    sf::RectangleShape healthBar;
    healthBar.setSize( sf::Vector2f( 300, 25 ) );
    healthBar.setPosition( sf::Vector2f( SCREEN_WIDTH - 315, 15));
    healthBar.setFillColor( sf::Color::White );
    healthBar.setOutlineThickness(5);
    healthBar.setOutlineColor( sf::Color::Black );

    sf::RectangleShape healthAmount;
    healthAmount.setSize( sf::Vector2f( this->player->getHealth() * 3, 25 ) );
    healthAmount.setPosition( sf::Vector2f( SCREEN_WIDTH - 315, 15 ) );
    healthAmount.setFillColor( sf::Color::Red );

    TextBlock HealthIndicator("health", &gameFont, sf::Color::Red, 30, true, sf::Vector2f(SCREEN_WIDTH - 430, 8));
    
    HealthIndicator.render(target);
    target.draw(healthBar);
    target.draw(healthAmount);

}
