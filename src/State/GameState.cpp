#include "GameState.hpp"
#include "MainMenuState.hpp"

void GameState::initFonts() 
{    
        
}

void GameState::initTextures()
{
    sf::Image playerSprite;
    playerSprite.loadFromFile("../assets/test_spritesheet.png");
    playerSprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["PLAYER_SHEET"].loadFromImage(playerSprite);

    sf::Image enemySprite;
    enemySprite.loadFromFile("../assets/dot.bmp");
    enemySprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["ENEMY_TEXTURE"].loadFromImage(enemySprite);

    floorTileTexture.loadFromFile("../assets/floortiles.jpg");
    floorTileTexture.setRepeated( true );
}

void GameState::initPlayers() 
{
    // @scawful
    // loading an image from a file to use as the sprite texture for the player
    // super temporary, just the begin
    
    this->enemy = new Enemy( 1200, 500, this->textures["ENEMY_TEXTURE"] );

    this->player = new Player( (SCREEN_WIDTH - playerTexture.getSize().x) / 2, (SCREEN_HEIGHT - playerTexture.getSize().y) / 2, this->textures["PLAYER_SHEET"] );
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->initFonts();
    this->initTextures();
    this->initPlayers();

    this->background.setTexture( &floorTileTexture );
    this->background.setTextureRect( sf::IntRect(0, 0, static_cast<float>(this->window->getSize().x * 4), static_cast<float>(this->window->getSize().y * 4)));
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>(this->window->getSize().x * 4),
              static_cast<float>(this->window->getSize().y * 4)
         )
    );
    //this->background.setFillColor(sf::Color::White);



    this->dungeonGenerator = new DungeonGenerator( 1, 75, 5, 5, 600, 600 );
    cout << "GameState::GameState created\n";
}

GameState::~GameState() 
{
    delete this->player;
    delete this->dungeonGenerator;
    cout << "GameState::~GameState destroyed\n";
}

void GameState::updateEnemyAI(const float& dt)
{
    // get the coordiantes and dimensions for the actors
    sf::Vector2f playerPosition = this->player->getPosition();
    sf::Vector2f playerSize = this->player->getSize();
    sf::Vector2f enemyPosition = this->enemy->getPosition();
    sf::Vector2f enemySize = this->enemy->getSize();

    sf::Vector2f trueCenter( playerPosition );
    trueCenter.x += this->player->getSize().x / 2;
    trueCenter.y += this->player->getSize().y / 2;

    sf::Vector2f enemyTrueCenter( enemyPosition );
    enemyTrueCenter.x -= (enemySize.x * 3) - enemySize.x / 2;
    enemyTrueCenter.y -= (enemySize.y * 3) - enemySize.y / 2;

    sf::Vector2f lineOfSightSize( enemySize.x * 6, enemySize.y * 6 );
    enemyLineOfSight.setPosition( sf::Vector2f( enemyTrueCenter.x, enemyTrueCenter.y ) );
    enemyLineOfSight.setFillColor( sf::Color( 255, 255, 255, 50 ));
    enemyLineOfSight.setOutlineThickness(2);
    enemyLineOfSight.setOutlineColor( sf::Color::Black );
    enemyLineOfSight.setSize( lineOfSightSize );

    sf::FloatRect playerRect( playerPosition.x, playerPosition.y, playerSize.x, playerSize.y );
    if ( enemyLineOfSight.getGlobalBounds().intersects( playerRect ) )
    {
        sf::Vector2f direction = this->enemy->normalize(trueCenter - enemyPosition);

        this->enemy->move( direction.x, direction.y, dt );
    }

}

void GameState::updateInput(const float& dt)
{

    // collide with edges of screen
    if ( this->player->getPosition().x < 0 ) 
    {
        this->player->setPosition( 0.f, this->player->getPosition().y );
    }
    else if ( this->player->getPosition().x > this->background.getSize().x - this->player->getSize().x ) 
    {
        this->player->setPosition( this->background.getSize().x - this->player->getSize().x, this->player->getPosition().y );
    }
    
    if ( this->player->getPosition().y < 0 ) 
    {
        this->player->setPosition( this->player->getPosition().x, 0.f );
    }
    else if ( this->player->getPosition().y > this->background.getSize().y - this->player->getSize().y ) 
    {
        this->player->setPosition( this->player->getPosition().x, this->background.getSize().y - this->player->getSize().y );
    }

    // dynamically fetch keyboard input in real time to move the player 
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
        this->player->move(-1.f, 0.f, dt);
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
        this->player->move(1.f, 0.f, dt);
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
        this->player->move(0.f, -1.f, dt);
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
        this->player->move(0.f, 1.f, dt);

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        this->player->setHealth( this->player->getHealth() + 1.f );
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        this->player->setHealth( this->player->getHealth() - 1.f );
}

void GameState::update(const float& dt)
{
    // always make sure to call functions of subclasses within the holding class
    // in this case we are calling the players update function inside of GameState
    this->player->update(dt);
    this->enemy->update(dt);
    this->updateEnemyAI(dt);
    this->updateInput(dt);
    this->updateKeytime(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    // tinfoil hat
    if (!target)
        target = this->window;

    // sets background to white for regions without objects being rendered over them
    target->clear(sf::Color::White);

    // the camera of the game, centered on the players position
    // viewports use the center rather than the top, left coordinates like the player
    // to compensate for a true center, we divide the players size in half and add that to the view coordinates
    sf::View dungeonView( sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
    sf::Vector2f trueCenter( this->player->getPosition() );
    trueCenter.x += this->player->getSize().x / 2;
    trueCenter.y += this->player->getSize().y / 2;
    dungeonView.setCenter( trueCenter );
    target->setView(dungeonView);

    // drawing the sf::Rectangle to the screen, which currently has an sf::Texture in it
    target->draw(this->background);

    //this->dungeonGenerator->render(*target);

    // the player class uses a reference argument, so we dereference the pointer to the RenderTarget
    this->player->render(*target);

    target->draw(this->enemyLineOfSight);
    this->enemy->render(*target);

    // ====================== //

    // creating a new view for the minimap of the dungeon generation output
    // currently not exactly sure why the width and height are larger than the object
    // increasing them seems to decrease the size of the view, which is odd. but okay
    sf::View minimapView ( sf::FloatRect(  0.75f, 0, 3000, 2400 ) );
    target->setView(minimapView);

    // draw the output of dungeonGenerator inside the minimap
    this->dungeonGenerator->render(*target);

    sf::RectangleShape playerRect;
    playerRect.setSize( sf::Vector2f( 20, 20 ) );
    playerRect.setPosition( sf::Vector2f( this->player->getPosition().x / (float)8.1, this->player->getPosition().y / (float)5.3) );
    playerRect.setFillColor( sf::Color::Magenta );
    target->draw(playerRect);

    // ====================== //
    sf::View guiView( sf::FloatRect(  0.75f, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
    target->setView(guiView);

    sf::RectangleShape healthBar;
    healthBar.setSize( sf::Vector2f( 300, 25 ) );
    healthBar.setPosition( sf::Vector2f( SCREEN_WIDTH - 315, 15));
    healthBar.setFillColor( sf::Color( 255, 255, 255, 0 ) );
    healthBar.setOutlineThickness(5);
    healthBar.setOutlineColor( sf::Color::Black );

    sf::RectangleShape healthAmount;
    healthAmount.setSize( sf::Vector2f( this->player->getHealth() * 3, 25 ) );
    healthAmount.setPosition( sf::Vector2f( SCREEN_WIDTH - 315, 15 ) );
    healthAmount.setFillColor( sf::Color::Red );

    target->draw(healthAmount);
    target->draw(healthBar);

}
