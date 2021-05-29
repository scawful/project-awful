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
    playerTexture.loadFromFile("../assets/dot.bmp");
    player = new Actor( 100, 100, playerTexture );
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
    delete player;
    cout << "GameState::~GameState destroyed\n";
}

void GameState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-10.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(10.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -10.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 10.f, dt);
}

void GameState::update(const float& dt)
{
    // temporary
    if ( this->changeState == "MainMenuState" )
    {
        this->states->push(new MainMenuState(this->window, this->states));
    }

    this->player->update(dt);
    this->updateInput(dt);
    this->updateKeytime(dt);
}

void GameState::render(sf::RenderTarget* target)
{

    if (!target)
        target = this->window;

    target->draw(this->background);
    player->render(*target);
}
