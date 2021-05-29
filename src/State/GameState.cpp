#include "GameState.hpp"
#include "MainMenuState.hpp"

void GameState::initFonts() 
{    
        
}

void GameState::initTextures()
{

}

void GameState::initPlayers() 
{
    // @scawful
    // loading an image from a file to use as the sprite texture for the player
    // super temporary, just the begin
    playerTexture.loadFromFile("../assets/dot.bmp");
    this->player = new Player( 100, 100, playerTexture );
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>(this->window->getSize().x),
              static_cast<float>(this->window->getSize().y)
         )
    );
    this->background.setFillColor(sf::Color::White);

    this->initFonts();
    this->initTextures();
    this->initPlayers();
    cout << "GameState::GameState created\n";
}

GameState::~GameState() 
{
    delete this->player;
    cout << "GameState::~GameState destroyed\n";
}

void GameState::updateInput(const float& dt)
{
    // dynamically fetch keyboard input in real time to move the player 
    // currently inputs based on velocity rather than unit vectors, gonna change that
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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
    if (!target)
        target = this->window;

    target->draw(this->background);

    // the player class uses a reference argument, so we dereference the pointer to the RenderTarget
    this->player->render(*target);
}
