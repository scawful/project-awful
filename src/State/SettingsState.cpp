#include "SettingsState.hpp"

// Initializer functions
void SettingsState::initVariables() 
{
    
}

/**
 * @brief Initialize the background size 
 * @author @scawful
 * 
 */
void SettingsState::initBackground() 
{
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>(this->window->getSize().x),
              static_cast<float>(this->window->getSize().y)
         )
    );
}

/**
 * @brief Load any fonts to be used in the SettingsState
 * @author @scawful
 * 
 */
void SettingsState::initFonts() 
{    
    if ( !this->menu_font.loadFromFile("../assets/ARCADECLASSIC.TTF") ) 
    {
        std::cout << "Error couldn't load menu font" << "\n";
    }
        
}

/**
 * @brief Initialize keybinds set by the user from a file 
 * @author @scawful
 * 
 */
void SettingsState::initKeybinds()
{
    std::fstream ifs("gamestate_binds.ini");

    if ( ifs.is_open() )
    {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

/**
 * @brief Load any Graphical objects to be used in the SettingsState
 * @author @scawful
 * 
 * @todo Separate this into multiple initialization functions (Buttons, DropDownLists, etc)
 * 
 */
void SettingsState::initGui() 
{

    this->buttons["EXIT_STATE"] = new Button(
                            sf::Vector2f( (SCREEN_WIDTH - 250.f) / 2, ((SCREEN_HEIGHT - 75.f) / 2) + 250.f ), 
                            sf::Vector2f(250.f, 75.f),
                            &this->menu_font, "Return", 30, true,
                            sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                            sf::Color(0x56A5ECcc), sf::Color(0x56A5ECbf), sf::Color(0x56A5ECb3));
    
    std::string li[] = { "1920x1080", "800x600", "640x480" };

    this->dropDownLists["RESOLUTION"] = new DropDown(sf::Vector2f((SCREEN_WIDTH - 250.f) / 2, 150), sf::Vector2f(250.f, 75.f), menu_font, li, 3);
}

/**
 * @brief Construct a new Settings State:: Settings State object
 * @author @scawful
 * 
 * @param window 
 * @param states 
 */
SettingsState::SettingsState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
}

/**
 * @brief Destroy the Settings State:: Settings State object
 * @author @scawful
 * 
 */
SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) 
    {
        delete it->second;
    }
    
    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2) 
    {
        delete it2->second;
    }
}

// Functions
void SettingsState::updateInput(const float & dt) 
{

}

/**
 * @brief Update GUI objects 
 * @author scawful
 * 
 * @todo Separate this into multiple functions 
 * 
 * @param dt 
 */
void SettingsState::updateGui(const float& dt)
{
    // Update all GUI elements in state and handles functionalty
    for (auto &it : this->buttons) 
    {
        it.second->update(this->mousePosView);
    }

    // Dropdown lists
    for (auto &it : this->dropDownLists) 
    {
        it.second->update(this->mousePosView, dt);
    }
    
    if (this->buttons["EXIT_STATE"]->isPressed()) 
    {
        this->endState();
    }
    
}

/**
 * @brief Cumulative update routine for the SettingsState
 * @author @scawful
 * 
 * @param dt 
 */
void SettingsState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);
    
    this->updateGui(dt);
}

/**
 * @brief Render any GUI Objects to the screen
 * @author @scawful
 * 
 * @todo separate function bing bong 
 * 
 * @param target 
 */
void SettingsState::renderGui(sf::RenderTarget& target)
{
    for (auto &it : this->buttons) 
    {
        it.second->render(target);
    }
    
    for (auto &it : this->dropDownLists) 
    {
        it.second->render(target);
    }
}

/**
 * @brief Cumulative render function for the SettingsState 
 * @author @scawful
 * 
 * @todo make the mouse text its own function (renderMouse)
 * 
 * @param target 
 */
void SettingsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    target->clear(sf::Color::Black);
    
    this->renderGui(*target);
    
    // Positional coordinates mouse tracing
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 20);
    mouseText.setFont(this->menu_font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}
