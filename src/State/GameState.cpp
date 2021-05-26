#include "GameState.hpp"

void GameState::initFonts() 
{    
        
}

void GameState::initTextures()
{

}

void GameState::initPlayers() 
{

}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>(this->window->getSize().x),
              static_cast<float>(this->window->getSize().y)
         )
    );
    this->background.setFillColor(sf::Color::Red);
    this->initFonts();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState() 
{

}

void GameState::updateInput(const float& dt)
{

}

void GameState::update(const float& dt)
{
    this->updateInput(dt);
    this->updateKeytime(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    //target->clear(sf::Color::Red);

    if (!target)
        target = this->window;

    target->draw(this->background);
}
