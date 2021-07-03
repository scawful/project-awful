#include "State.hpp"

State::State(sf::RenderWindow* window, std::stack<State*>* states) 
{
    this->window = window;
    this->states = states;
    this->quit = false;
    this->paused = false;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
}

State::~State() 
{
    
}

// Accessors
const bool & State::getQuit() const 
{
    return this->quit;
}

const bool State::getKeytime()
{
    if ( this->keytime >= this->keytimeMax ) 
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

// Functions 
void State::endState() 
{
    this->quit = true;
    {
        sf::Clock t1;
        while (t1.getElapsedTime().asMilliseconds() <= 150.f) {
            continue;
        }
    }   
}

void State::pauseState() 
{
    this->paused = true;
}
void State::unpauseState() 
{
    this->paused = false;
}

void State::updateMousePositions() 
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 100.f * dt;
}

