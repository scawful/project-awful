#include "State.hpp"

/**
 * @brief Construct a new State:: State object
 *        Set state variables default values 
 * 
 * @todo change states stack to a shared or smart pointer + thoroughly test
 * 
 * @param window 
 * @param states 
 */
State::State(sf::RenderWindow* window, std::stack<State*>* states) 
{
    this->window = window;
    this->states = states;
    this->quit = false;
    this->paused = false;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
}

/**
 * @brief Destroy the State:: State object
 * 
 */
State::~State() 
{
    
}

/**
 * @brief Quit attribute accessor
 * 
 * @return true 
 * @return false 
 */
const bool & State::getQuit() const 
{
    return this->quit;
}

/**
 * @brief Keytime attribute accessor
 * 
 * @return true 
 * @return false 
 */
const bool State::getKeytime()
{
    if ( this->keytime >= this->keytimeMax ) 
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

/**
 * @brief End the current state
 * 
 */
void State::endState() 
{
    this->quit = true; 
}

/**
 * @brief Pause the current state 
 * 
 */
void State::pauseState() 
{
    this->paused = true;
}

/**
 * @brief Unpause the current state
 * 
 */
void State::unpauseState() 
{
    this->paused = false;
}

/**
 * @brief Update the mouse position using sf::Mouse
 * 
 */
void State::updateMousePositions() 
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

/**
 * @brief Update the keytime variable 
 * 
 * @param dt 
 */
void State::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 100.f * dt;
}

