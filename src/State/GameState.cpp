#include "GameState.hpp"
#include "MainMenuState.hpp"

/**
 * @brief Load any desired TTF fonts for the GameState
 * @author @scawful
 * 
 */
void GameState::initFonts()
{
    if (!this->gameFont.loadFromFile("../assets/ARCADECLASSIC.TTF")) 
    {
        std::cout << "Error couldn't load game font" << "\n";
    }   
}

/**
 * @brief Load any desired image textures for the GameState
 * @author @scawful
 * 
 */
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

/**
 * @brief Load the Player character and their spritesheet
 * @author @scawful
 * 
 */
void GameState::initPlayers()
{
    this->player = new Player( (SCREEN_WIDTH - this->textures["PLAYER_SHEET"].getSize().x) / 2, 
                            (SCREEN_HEIGHT - this->textures["PLAYER_SHEET"].getSize().y) / 2, 
                            this->textures["PLAYER_SHEET"] );
}

/**
 * @brief Load the state of the game world to be displayed
 * @author @scawful
 * 
 */
void GameState::initWorld()
{
    currentWorld = new Underworld( this->player, this->textures );
}

/**
 * @brief Create any buttons to be displayed in the GameState
 * @author @scawful
 * 
 */
void GameState::initButtons()
{
    this->buttons["MAIN_MENU_BTN"] = new Button(
                        sf::Vector2f( 10, 10 ),
                        sf::Vector2f( 250.f, 50.f ),
                        &this->gameFont, "Return to Main Menu", 24, true,
                        sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color(0x56A5ECb3));

}

/**
 * @brief Construct a new Game State:: Game State object
 * @author @scawful
 * 
 * @param window 
 * @param states 
 */
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->initFonts();
    this->initTextures();
    this->initPlayers();
    this->initWorld();
    this->initButtons();

    cout << "GameState::GameState created\n";
}

/**
 * @brief Destroy the Game State:: Game State object
 * @author @scawful 
 * 
 */
GameState::~GameState() 
{
    //delete this->playerSword;

    auto it = this->buttons.begin();
    for ( it = this->buttons.begin(); it != this->buttons.end(); ++it ) 
    {
        delete it->second;
    }

    delete currentWorld;
    currentWorld = NULL;

    delete this->player;
    player = NULL;

    cout << "GameState::~GameState destroyed\n";
}

/**
 * @brief Update any input from the User for GUI, Player or Debug controls 
 * 
 * @param dt 
 */
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

/**
 * @brief Update the state of any buttons present on the screen 
 * 
 */
void GameState::updateButtons()
{
    for (auto &it : this->buttons) 
    {
        it.second->update(this->mousePosView);
    }
    
    // Return to MainMenuState from GameState
    if ( this->buttons["MAIN_MENU_BTN"]->isPressed() ) 
    {
        this->endState();
    }

    // maybe put a pause menu button in here ?

}

/**
 * @brief cumulative update function 
 * @author @scawful
 * 
 * @param dt 
 */
void GameState::update(const float& dt)
{
    //this->playerSword->update(dt);
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
    this->updateKeytime(dt);
    currentWorld->update(dt);
}

/**
 * @brief Render any initialized buttons to the sf::RenderTarget\
 * @author @scawful
 * 
 * @param target 
 */
void GameState::renderButtons( sf::RenderTarget& target )
{
    for ( auto &it : this->buttons )
    {
        it.second->render(target);
    }
}

/**
 * @brief Cumulative render function using the sf::RenderTarget
 * @author @scawful
 * 
 * @param target 
 */
void GameState::render( sf::RenderTarget* target )
{
    // tinfoil hat
    if ( !target )
        target = this->window;

    // sets background to white for regions without objects being rendered over them
    target->clear( sf::Color::Black );

    currentWorld->render(*target);
    
    this->renderButtons(*target);
}
