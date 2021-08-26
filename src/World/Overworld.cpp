#include "Overworld.hpp"

void Overworld::initFonts()
{
    this->gameFont.loadFromFile("../assets/ARCADECLASSIC.TTF");
}

void Overworld::initTextures() 
{
    // load individual enemy images 
    sf::Image enemySprite;
    enemySprite.loadFromFile("../assets/ghost.png");
    enemySprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["ENEMY_TEXTURE"].loadFromImage(enemySprite);

    enemySprite.loadFromFile("../assets/ghost2.png");
    enemySprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["GHOST2"].loadFromImage(enemySprite);

    enemySprite.loadFromFile("../assets/ghost3.png");
    enemySprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["GHOST3"].loadFromImage(enemySprite);

    // set tiled texture floor 
    floorTileTexture.loadFromFile("../assets/floortiles.jpg");
    floorTileTexture.setRepeated( true );
}

void Overworld::initPlayers()
{
    playerSize = this->player->getSize();
    playerPosition = this->player->getPosition();
}

void Overworld::initEnemies() 
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    // 10 : num enemies to create
    for ( int i = 0; i < 10; i++ )
    {
        uniform_int_distribution<int> randomPositionX(0, SCREEN_WIDTH * 4 );
        uniform_int_distribution<int> randomPositionY(0, SCREEN_HEIGHT * 4 );
        
        int new_x = randomPositionX(rng);
        int new_y = randomPositionY(rng);

        uniform_int_distribution<int> randomEnemy(0, 3);
        int random_enemy = randomEnemy(rng);

        Enemy *newEnemy = NULL;
        switch (random_enemy)
        {
            case 1:
                newEnemy = new Enemy( new_x, new_y, this->textures["ENEMY_TEXTURE"] );
                break;
            case 2:
                newEnemy = new Enemy( new_x, new_y, this->textures["GHOST2"] );
                break;
            case 3:
                newEnemy = new Enemy( new_x, new_y, this->textures["GHOST3"] );
                break;
            default:
                newEnemy = new Enemy( new_x, new_y, this->textures["ENEMY_TEXTURE"] );
                break;
        }

        this->enemies.push_back( newEnemy );
    }

}

Overworld::Overworld( Player *playerRef, std::map<std::string, sf::Texture> &textureRef ) : World( playerRef, textureRef )
{
    this->initFonts();
    this->initTextures();
    this->initPlayers();
    this->initEnemies();

    this->background.setTexture( &floorTileTexture );
    this->background.setTextureRect( sf::IntRect(0, 0, static_cast<float>(SCREEN_WIDTH * 4), 
                                                       static_cast<float>(SCREEN_HEIGHT * 4)));
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>( SCREEN_WIDTH * 4 ),
              static_cast<float>( SCREEN_HEIGHT * 4 )
         )
    );

    cout << "Overworld created" << endl;
    
}

Overworld::~Overworld() 
{
    for ( int i = 0; i < 10; i++ )
        delete this->enemies[i];
    
    cout << "Overworld destroyed" << endl;
}


void Overworld::updateEnemyAI(const float& dt)
{
    sf::Vector2f trueCenter( playerPosition );
    trueCenter.x += this->player->getSize().x / 2;
    trueCenter.y += this->player->getSize().y / 2;

    // multiple enemies 
    for ( int i = 0; i < 10; i++ )
    {
        // get the coordiantes and dimensions for the actors
        sf::Vector2f enemiesPosition = this->enemies[i]->getPosition();
        sf::Vector2f enemiesSize = this->enemies[i]->getSize();

        sf::Vector2f enemiesTrueCenter( enemiesPosition );
        enemiesTrueCenter.x -= (enemiesSize.x * 3) - enemiesSize.x / 2;
        enemiesTrueCenter.y -= (enemiesSize.y * 3) - enemiesSize.y / 2;

        sf::Vector2f lineOfSightSize( enemiesSize.x * 6, enemiesSize.y * 6 );

        enemySights[i].setPosition( sf::Vector2f( enemiesTrueCenter.x, enemiesTrueCenter.y ) );
        enemySights[i].setFillColor( sf::Color( 255, 255, 255, 50 ));
        enemySights[i].setOutlineThickness(2);
        enemySights[i].setOutlineColor( sf::Color::Black );
        enemySights[i].setSize( lineOfSightSize );

        sf::FloatRect playerRect( playerPosition.x, playerPosition.y, playerSize.x, playerSize.y );
        if ( enemySights[i].getGlobalBounds().intersects( playerRect ) )
        {
            sf::Vector2f direction = this->enemies[i]->normalize(trueCenter - enemiesPosition);

            this->enemies[i]->move( direction.x, direction.y, dt );
        }
    }

}

void Overworld::updateInput(const float& dt)
{
    // collide with edges of screen
    if ( playerPosition.x < 0 ) 
        this->player->setPosition( 0.f, playerPosition.y );
    else if ( playerPosition.x > this->background.getSize().x - playerSize.x ) 
        this->player->setPosition( this->background.getSize().x - playerSize.x, playerPosition.y );

    if ( playerPosition.y < 0 ) 
        this->player->setPosition( playerPosition.x, 0.f );
    else if ( playerPosition.y > this->background.getSize().y - playerSize.y ) 
        this->player->setPosition( playerPosition.x, this->background.getSize().y - playerSize.y );

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

void Overworld::update(const float& dt) 
{
    playerPosition = this->player->getPosition();
    this->player->update(dt);

    for ( int i = 0; i < 10; i++)
        this->enemies[i]->update(dt);

    this->updateEnemyAI(dt);
    this->updateInput(dt);
}

void Overworld::render(sf::RenderTarget &target) 
{
    // sets background to white for regions without objects being rendered over them
    target.clear( sf::Color::White );

    // the camera of the game, centered on the players position
    // viewports use the center rather than the top, left coordinates like the player
    // to compensate for a true center, we divide the players size in half and add that to the view coordinates
    sf::View dungeonView( sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
    sf::Vector2f trueCenter( this->player->getPosition() );
    trueCenter.x += playerSize.x / 2;
    trueCenter.y += playerSize.y / 2;
    dungeonView.setCenter( trueCenter );
    target.setView(dungeonView);

    // drawing the sf::Rectangle to the screen, which currently has an sf::Texture in it
    target.draw(this->background);

    this->player->render(target);

    // render enemies and their line of sights for debugging purposes
    for ( int i = 0; i < 10; i++)
    {
        target.draw(this->enemySights[i]);
        this->enemies[i]->render(target);
    }

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
