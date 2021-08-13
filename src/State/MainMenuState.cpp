#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"

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


void MainMenuState::initButtons()
{
    
    this->buttons["GAME_STATE_BTN"] = new Button(
                        sf::Vector2f((SCREEN_WIDTH - 250.f) / 2, (SCREEN_HEIGHT - 75.f) / 2), // position
                        sf::Vector2f(250.f, 75.f), // size 
                        &this->menu_font, "New Game", 30, true,
                        sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color(0x56A5ECb3));
                        // idle                 hover                      active
                        // 0xRRGGBBAA 
                        // RRR, GGG, BBB, AAA

    this->buttons["SETTINGS_STATE_BTN"] = new Button(
                        sf::Vector2f((SCREEN_WIDTH - 250.f) /2, ((SCREEN_HEIGHT - 75.f) / 2) + 125.f ),
                        sf::Vector2f(250.f, 75.f),
                        &this->menu_font, "Settings", 30, true, 
                        sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color(0x56A5ECb3));
    
    
    this->buttons["QUIT_GAME_BTN"] = new Button(
                        sf::Vector2f((SCREEN_WIDTH - 250.f) / 2, ((SCREEN_HEIGHT - 75.f) / 2) + 250.f),
                        sf::Vector2f(250.f, 75.f),
                        &this->menu_font, "Quit Game", 30, true, 
                        sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color(0x56A5ECb3));
    
}


void MainMenuState::initTextboxes () {
    this->textboxes["CHARACTER_NAME"] = new Textbox (
                        sf::Vector2f((SCREEN_WIDTH - 450.f) / 2, ((SCREEN_HEIGHT - 50.f) / 2) - 250.f),
                        sf::Vector2f(450.f, 50.f),
                        &this->menu_font, 30, 23, 
                        sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color::Black,
                        sf::Color(225, 231, 238, 200), sf::Color(244, 244, 244, 200), sf::Color::White, true, "Enter Your Character Name");
}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, sf::Event *Event)
    : State(window, states)
{
    this->sfEvent = Event;
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initButtons();
    this->initTextboxes();

    cout << "MainMenuState::MainMenuState created\n";
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for ( it = this->buttons.begin(); it != this->buttons.end(); ++it ) 
    {
        delete it->second;
    }

    auto rep = this->textboxes.begin();
    for (rep = this->textboxes.begin(); rep != this->textboxes.end(); ++rep) 
    {
        delete rep->second;
    }

    cout << "MainMenuState::~MainMenuState destroyed\n";
}


void MainMenuState::updateInput(const float &dt) 
{
    if (!this->getKeytime()) {
        this->updateKeytime(dt);
    }
}


void MainMenuState::updateButtons()
{
    // Update all buttons in state and handles functionalty
    for (auto &it : this->buttons) 
    {
        it.second->update(this->mousePosView);
    }
    
    if ( this->buttons["GAME_STATE_BTN"]->isPressed() ) 
    {
        this->states->push(new GameState(this->window, this->states));
    }

    if ( this->buttons["SETTINGS_STATE_BTN"]->isPressed() ) 
    {
        this->states->push(new SettingsState(this->window, this->states));
    }
    
    if ( this->buttons["QUIT_GAME_BTN"]->isPressed() )
    {
        this->endState();
    }
}


void MainMenuState::updateTextboxes () 
{
    for (auto &it : this->textboxes)
    {
        it.second->update(this->mousePosView, *this->sfEvent);
    }
}


void MainMenuState::update(const float& dt) 
{
    // updateMousePositions comes from the parent State class, will be useful for GUI buttons 
    this->updateMousePositions();
    this->updateInput(dt); 

    this->updateButtons();
    this->updateTextboxes();
}


void MainMenuState::renderButtons(sf::RenderTarget& target)
{
    for ( auto &it : this->buttons ) 
    {
        it.second->render(target);
    }
}


void MainMenuState::renderTextbox(sf::RenderTarget& target) 
{
    for (auto &it : this->textboxes)
    {
        it.second->render(target);
    }
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

    // render the buttons
    this->renderButtons(*target);

    // render the textbox
    this->renderTextbox(*target);
        
    // Create the text for the title
    TextBlock title("Project Awful", &menu_font, sf::Color::Black, 60, true);
    title.setPosition( (SCREEN_WIDTH - title.getLocalBounds().width) / 2 , 30);
    title.render(*target);

    // Positional coordinates mouse tracing
    TextBlock mouseText ("", &menu_font, sf::Color::Black, 12, false);
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
   
    stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}
