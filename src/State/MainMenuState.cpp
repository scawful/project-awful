#include "MainMenuState.hpp"
#include "GameState.hpp"

// Initializer functions
void MainMenuState::initVariables() 
{
    
}

void MainMenuState::initBackground() 
{
    // set the size for the white background equal to the size of the window itself
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
    // this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts() 
{    
    // loading the font to be used for the title and mouse cursor position display
    if (!this->menu_font.loadFromFile("../assets/ARCADECLASSIC.TTF")) 
    {
        std::cout << "Error couldn't load menu font" << "\n";
    }       
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    cout << "MainMenuState::MainMenuState created\n";
}

MainMenuState::~MainMenuState()
{
    cout << "MainMenuState::~MainMenuState destroyed\n";
}


void MainMenuState::updateInput(const float & dt) 
{
    
}

void MainMenuState::update(const float& dt) 
{
    // updateMousePositions comes from the parent State class, will be useful for GUI buttons 
    this->updateMousePositions();
    this->updateInput(dt); 
}

void MainMenuState::render(sf::RenderTarget* target)
{
    // if the target for whatever reason is invalid, attempt to render to the whole window
    if (!target)
        target = this->window;

    // reset the view 
    sf::View menuView( sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) );
    target->setView( menuView );
    
    // draw the white background
    target->draw(this->background);
        
    // Create the text for the title
    sf::Text title;
    title.setString("Project Awful");
    title.setFillColor(sf::Color::Black);
    title.setFont(this->menu_font);
    title.setCharacterSize(60);
    title.setPosition( (SCREEN_WIDTH - title.getLocalBounds().width) / 2 , 30);
    target->draw(title);

    sf::Text prompt;
    prompt.setString("Press Space to begin");
    prompt.setFillColor(sf::Color::Black);
    prompt.setFont(this->menu_font);
    prompt.setCharacterSize(28);
    prompt.setPosition( (SCREEN_WIDTH - prompt.getLocalBounds().width) / 2 , 400);
    target->draw(prompt);
    
    // Positional coordinates mouse tracing
    sf::Text mouseText;
    mouseText.setFillColor(sf::Color::Black);
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
    mouseText.setFont(this->menu_font);
    mouseText.setCharacterSize(12);

    stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}
