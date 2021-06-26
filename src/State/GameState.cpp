#include "GameState.hpp"
#include "MainMenuState.hpp"

void GameState::initTextures()
{
    // load player spritesheet
    sf::Image playerSprite;
    playerSprite.loadFromFile("../assets/test_spritesheet.png");
    playerSprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["PLAYER_SHEET"].loadFromImage(playerSprite);

    sf::Image swordSprite;
    swordSprite.loadFromFile("../assets/sword.png");
    swordSprite.createMaskFromColor(sf::Color(0, 255, 0, 255));
    this->textures["SWORD"].loadFromImage( swordSprite );
}

void GameState::initPlayers()
{
    this->player = new Player( (SCREEN_WIDTH - this->textures["PLAYER_SHEET"].getSize().x) / 2, 
                            (SCREEN_HEIGHT - this->textures["PLAYER_SHEET"].getSize().y) / 2, 
                            this->textures["PLAYER_SHEET"] );
}

void GameState::initWorld()
{
    currentWorld = new Overworld( this->player, this->textures );
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->initTextures();
    this->initPlayers();
    this->initWorld();

    cout << "GameState::GameState created\n";
}

GameState::~GameState() 
{
    //delete this->playerSword;

    delete currentWorld;
    currentWorld = NULL;

    delete this->player;
    player = NULL;

    cout << "GameState::~GameState destroyed\n";
}

void GameState::updateInput(const float& dt)
{
    // sword
    // swordPosition.x = playerPosition.x + 10;
    // swordPosition.y = playerPosition.y + 20;
    // this->playerSword->move( swordPosition.x, swordPosition.y, dt );

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Enter ) )
    {
        delete currentWorld;
        currentWorld = NULL;

        currentWorld = new Underworld( this->player, this->textures );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::RShift ) )
    {
        delete currentWorld;
        currentWorld = NULL;

        currentWorld = new Overworld( this->player, this->textures );
    }

}

void GameState::update(const float& dt)
{
    //this->playerSword->update(dt);
    
    this->updateInput(dt);
    this->updateKeytime(dt);
    currentWorld->update(dt);
}

void GameState::render( sf::RenderTarget* target )
{
    // tinfoil hat
    if ( !target )
        target = this->window;

    // sets background to white for regions without objects being rendered over them
    target->clear( sf::Color::White );

    currentWorld->render(*target);
}
