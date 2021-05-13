#include "MainMenuState.hpp"

// Initializer functions
void MainMenuState::initVariables() 
{
    
}

void MainMenuState::initBackground() 
{
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>(this->window->getSize().x),
              static_cast<float>(this->window->getSize().y)
         )
    );
    
    // if (!this->backgroundTexture.loadFromFile("background.jpg")) 
    // {
    //     throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    // }
    
    //this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts() 
{    
    if (!this->menu_font.loadFromFile("../assets/ARCADECLASSIC.TTF")) 
    {
        std::cout << "Error couldn't load menu font" << "\n";
    }       
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::updateInput(const float & dt) 
{

}

void MainMenuState::update(const float& dt) 
{
    this->updateMousePositions();
    this->updateInput(dt); 
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->draw(this->background);
        
    // Literally the title lmao
    sf::Text title;
    title.setString("Project Awful");
    title.setFillColor(sf::Color::Black);
    title.setFont(this->menu_font);
    title.setCharacterSize(60);
    title.setPosition( (1920 - title.getLocalBounds().width) / 2 , 30);
    target->draw(title);
    
    // Positional coordinates mouse tracing
    sf::Text mouseText;
    mouseText.setFillColor(sf::Color::Black);
    mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 20);
    mouseText.setFont(this->menu_font);
    mouseText.setCharacterSize(24);
    stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}
