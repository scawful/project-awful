#include "Underworld.hpp"

void Underworld::initTextures() 
{
    
}

void Underworld::initPlayers()
{
    this->playerSize = this->player->getSize();
    this->playerPosition = this->player->getPosition();
}

void Underworld::initEnemies() 
{
    
}

Underworld::Underworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef ) : World( playerRef, textureRef )
{
    this->dungeonGenerator = new DungeonGenerator( 1, 150, 5, 5, SCREEN_HEIGHT, SCREEN_HEIGHT);

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
    target.clear( sf::Color::Red );
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

    // creating a new view for the minimap of the dungeon generation output
    // currently not exactly sure why the width and height are larger than the object
    // increasing them seems to decrease the size of the view, which is odd. but okay
    sf::View minimapView ( sf::FloatRect(  0.75f, 0, 3000, 2400 ) );
    target.setView(minimapView);

    // draw the output of dungeonGenerator inside the minimap
    this->dungeonGenerator->render(target);

    sf::RectangleShape playerRect;
    playerRect.setSize( sf::Vector2f( 20, 20 ) );
    playerRect.setPosition( sf::Vector2f( playerPosition.x / (float)8.1, playerPosition.y / (float)5.3) );
    playerRect.setFillColor( sf::Color::Magenta );
    target.draw(playerRect);

}
