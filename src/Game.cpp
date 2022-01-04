#include "Game.hpp"

/**
 * @brief set default variables for game runtime 
 * @author @scawful
 * 
 */
void Game::initVariables() 
{
    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
}

/**
 * @brief initialization of game window via sfml RenderWindow
 * @author @scawful
 * 
 * @todo add a config file with saved settings to import from 
 * 
 */
void Game::initWindow() 
{    
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    string title = "Project Awful";
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;
    
    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    
    // Create the main window
    if ( this->fullscreen )
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
    else
        this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, window_bounds.bitsPerPixel), title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
    
    // if (!this->icon.loadFromFile("icon.png"))
    //     std::cout << "Error couldn't open icon" << "\n";
    
    //this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());

}

/**
 * @brief push the initial state of the game to the stack 
 * @author @scawful 
 * 
 */
void Game::initStates() 
{
    // add the MainMenuState to the stack of States 
    this->states.push(new MainMenuState(this->window, &this->states, this->sfEvent));
    this->states.top()->currentState = "MainMenuState";
}

/**
 * @brief Construct a new Game:: Game object
 * @author @scawful
 * 
 */
Game::Game() 
{
    // @scawful: commenting out debug lines for the master branch 
    // cout << "Game::constructor - dev test" << endl;
    this->sfEvent = make_shared<sf::Event>();
    this->initWindow();
    this->initStates();
}

/**
 * @brief Destroy the Game:: Game object
 * @author @scawful
 * 
 */
Game::~Game()
{
    // dispose of the sfml window instance and pop any remaining states off the stack
    delete this->window;
    while( !this->states.empty() ) 
    {
        delete this->states.top();
        this->states.pop();
    }
}

/**
 * @brief handles delta time clock refresh 
 * @author @scawful
 * 
 */
void Game::updateDt() 
{
    // Updates delta time variable with update/render time for one frame
    this->dt = this->dtClock.restart().asSeconds();
}

/**
 * @brief universal event handling 
 * @author @scawful
 * 
 */
void Game::updateSFMLEvents() 
{
    // polling events from sfml using the sf::Event class
    // handles inputs across the entire game, such as escape for menus
    // currently escape closes the game, but when we make the PauseMenu it will open that
    while ( this->window->pollEvent(*this->sfEvent.get()) )
    {
        // Close window: exit
        if (this->sfEvent.get()->type == sf::Event::Closed ) 
        {
            this->window->close();
        }

        // Jacob: Commented out for Textbox testing purposes
        // if ( this->sfEvent.type == sf::Event::KeyPressed )
        // {
        //     if ( this->sfEvent.key.code == sf::Keyboard::Escape )
        //     {
        //         this->window->close();
        //     }
        // }
    }
}

/**
 * @brief primary update function which handles the current state on the stack
 * @author @scawful
 * 
 */
void Game::update() 
{
    this->updateSFMLEvents();
    
    // updating anything that happens inside of the states 
    // passing in the delta time to help with consistent animations later on
    // checks if any of the states are attempting to quit, so it can properly clean them off the stack
    if( !this->states.empty() ) 
    {    
        this->states.top()->update(this->dt);
        if ( this->states.top()->getQuit() ) 
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    } 
    else 
    {
        this->window->close();
    }
}

/**
 * @brief primary render function for top of stack state 
 * @author @scawful
 * 
 */
void Game::render() 
{
    // Clear screen
    this->window->clear();

    // render items
    if ( !this->states.empty() )
        this->states.top()->render();

    // Update the window
    this->window->display();
}

/**
 * @brief main game loop
 * @author @scawful
 * 
 */
void Game::run() 
{
    while ( this->window->isOpen() )
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
