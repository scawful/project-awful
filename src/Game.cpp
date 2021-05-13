#include "Game.hpp"

//Initializer Functions
void Game::initVariables() 
{
    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::initWindow() 
{    
    string title = "Project Awful";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
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
        this->window = new sf::RenderWindow(sf::VideoMode(800, 600, window_bounds.bitsPerPixel), title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
    
    // if (!this->icon.loadFromFile("icon.png"))
    //     std::cout << "Error couldn't open icon" << "\n";
    
    //this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());

}

void Game::initStates() 
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}


//Constructors / Destructors
Game::Game() 
{
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while(!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void Game::updateDt() 
{
    // Updates delta time variable with update/render time for one frame
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {

    while (this->window->pollEvent(sfEvent))
    {
        // Close window: exit
        if (this->sfEvent.type == sf::Event::Closed) 
        {
//            this->states.top()->endState();
//            delete this->states.top();
//            this->states.pop();
            this->window->close();
        }
        
        // Escape pressed: exit
       if (this->sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) {
          this->window->close();
       }
    }

}

void Game::update() {
    this->updateSFMLEvents();
    
    if(!this->states.empty()) 
    {    
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit()) {
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

void Game::render() 
{
    // Clear screen
    this->window->clear();

    // render items
    if(!this->states.empty())
        this->states.top()->render();

    // Update the window
    this->window->display();
}

void Game::run() 
{
    // Start the game loop
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
