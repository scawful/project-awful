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
    target->clear(sf::Color::Red);

    if (!target)
        target = this->window;
}
