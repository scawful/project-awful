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

    floorTileTexture.loadFromFile("../assets/floortiles.jpg");
    floorTileTexture.setRepeated( true );
}

void GameState::initPlayers() 
{
    // @scawful
    // loading an image from a file to use as the sprite texture for the player
    // super temporary, just the begin
    //playerTexture.loadFromFile("../assets/dot.bmp");
    //this->player = new Player( 0, 0, playerTexture );

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
}

void GameState::update(const float& dt)
{
    // always make sure to call functions of subclasses within the holding class
    // in this case we are calling the players update function inside of GameState
    this->player->update(dt);
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
}
