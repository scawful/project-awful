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

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ESCAPE")))  && this->getKeytime()) 
    {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateKeytime(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
}
