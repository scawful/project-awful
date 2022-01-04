#include "CharacterState.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

/**
 * @brief Initialize font for the CharacterState
 * @author @scawful
 * 
 */
void CharacterState::initFonts() 
{
    if (!this->characterFont.loadFromFile("../assets/A_Goblin_Appears!.otf")) 
    {
        cout << "Error couldn't load character font" << "\n";
    }  
}

/**
 * @brief Initialize background texture 
 * @author @scawful
 * 
 */
void CharacterState::initTextures() 
{
    this->background.setSize(
         sf::Vector2f
         (
              static_cast<float>(this->window->getSize().x),
              static_cast<float>(this->window->getSize().y)
         )
    );

    if (!this->backgroundTexture.loadFromFile("../assets/menu_background.png")) 
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }
    this->background.setTexture(&this->backgroundTexture);
}

/**
 * @brief Initialize any buttons for the CharacterState
 * @author @scawful
 * 
 */
void CharacterState::initButtons()
{
    this->buttons["CONFIRM_BTN"] = new Button(
                        sf::Vector2f(((SCREEN_WIDTH - gui_size_x) / 2) * 1.25, SCREEN_HEIGHT - gui_size_y - gui_offset), // position
                        sf::Vector2f(gui_size_x, gui_size_y), // size 
                        &this->characterFont, "==>", 30, true,
                        sf::Color::White, sf::Color::White, sf::Color::White,
                        //sf::Color(0x42dd22cc), sf::Color(0x4af626cc), sf::Color(0x4af626cc),
                        sf::Color::Black, sf::Color::Black, sf::Color::Black);
                        // idle                 hover                      active
                        // 0xRRGGBBAA 
                        // RRR, GGG, BBB, AAA

    this->buttons["BACK_BTN"] = new Button(
                    sf::Vector2f(((SCREEN_WIDTH - gui_size_x) / 2) * 0.75, (SCREEN_HEIGHT - gui_size_y - gui_offset)), // position
                    sf::Vector2f(gui_size_x, gui_size_y), // size 
                    &this->characterFont, "<==", 30, true,
                    sf::Color::White, sf::Color::White, sf::Color::White,
                    //sf::Color(0x42dd22cc), sf::Color(0x4af626cc), sf::Color(0x4af626cc),
                    sf::Color::Black, sf::Color::Black, sf::Color::Black);
    
}

/**
 * @brief Initialize any dropdown menus to be used in the CharacterState
 * @author @scawful
 * 
 */
void CharacterState::initDropdowns()
{
    float dropdown_modifier = 0.275;

    this->text_blocks["GENDER"] = new TextBlock("Gender", &characterFont, sf::Color::White, 24, true);
    std::string li[] = { "Male", "Female" };

    this->dropDownLists["GENDER"] = new DropDown(sf::Vector2f(gui_offset, SCREEN_HEIGHT * dropdown_modifier), sf::Vector2f(gui_size_x, gui_size_y), characterFont, li, 2);
    this->dropDownLists["GENDER"]->setColors( sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Black, sf::Color::Black, sf::Color::Black );
    this->text_blocks["GENDER"]->setPosition( (gui_size_x / 2) - gui_offset, (SCREEN_HEIGHT * dropdown_modifier) - this->text_blocks["GENDER"]->getCharacterSize() );


    this->text_blocks["CLASS"] = new TextBlock("Class", &characterFont, sf::Color::White, 24, true);
    std::string char_class[] = { "Warrior", "Assassin", "Mage", "Archer" };

    this->dropDownLists["CLASS"] = new DropDown(sf::Vector2f((gui_offset * 2) + gui_size_x, SCREEN_HEIGHT * dropdown_modifier), 
                                                sf::Vector2f(gui_size_x, gui_size_y), 
                                                characterFont, char_class, 4);

    this->dropDownLists["CLASS"]->setColors( sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::Black, sf::Color::Black, sf::Color::Black );

    this->text_blocks["CLASS"]->setPosition( (gui_offset * 5) + gui_size_x , (SCREEN_HEIGHT * dropdown_modifier) - this->text_blocks["GENDER"]->getCharacterSize() );
}

/**
 * @brief Initialize any TextBox objects to be used in the Character State
 * @authors @jmielc2 @scawful
 * 
 */
void CharacterState::initTextboxes () 
{
    this->textboxes["CHARACTER_NAME"] = new Textbox (
                        sf::Vector2f(SCREEN_WIDTH * 0.025, SCREEN_HEIGHT * 0.2),
                        sf::Vector2f(gui_size_x * 2, gui_size_y),
                        &this->characterFont, 18, 23, 
                        sf::Color::White, sf::Color::White, sf::Color::White,
                        //sf::Color(0x3bc41ecc), sf::Color(0x42dd22cc), sf::Color(0x3bc41ecc),
                        sf::Color::Black, sf::Color::Black, sf::Color::Black,
                         true, "> Enter Name");
}

/**
 * @brief Construct a new Character State:: Character State object
 * @authors @scawful
 * 
 * @param window 
 * @param states 
 * @param event 
 */
CharacterState::CharacterState(sf::RenderWindow* window, std::stack<State*>* states, shared_ptr<sf::Event> event) : State(window, states)
{
    current_substate = 0;
    gui_offset = 20.f;
    gui_size_x = 200.f;
    gui_size_y = 50.f;
    this->sfEvent = event;
    this->initFonts();
    this->initTextures();
    this->initButtons();
    this->initDropdowns();
    this->initTextboxes();
    cout << "CharacterState created!" << endl;
}

/**
 * @brief Destroy the Character State:: Character State object
 * @author @scawful
 * 
 */
CharacterState::~CharacterState() 
{
    for ( auto& btn : buttons ) 
    {
        delete btn.second;
    }

    for ( auto& txtbx : textboxes ) 
    {
        delete txtbx.second;
    }

    for ( auto& dropdown : dropDownLists ) 
    {
        delete dropdown.second;
    }

}

/**
 * @brief Update input for the Character State
 * @author @scawful
 * 
 * @param dt 
 */
void CharacterState::updateInput(const float &dt) 
{
    if (!this->getKeytime()) {
        this->updateKeytime(dt);
    }
}

/**
 * @brief Update any buttons that have been initialized 
 * @author @scawful
 * 
 */
void CharacterState::updateButtons()
{
    // Update all buttons in state and handles functionalty
    for (auto &it : this->buttons) 
    {
        it.second->update(this->mousePosView);
    }
    
    if ( this->buttons["CONFIRM_BTN"]->isPressed() )
    {
        current_substate++;
        // this->endState();
    }

    if ( this->buttons["BACK_BTN"]->isPressed() )
    {
        if ( current_substate > 0 )
        {
            current_substate--;
        }
        else
        {
            this->endState();
        }
    }
}

/**
 * @brief Update any dropdown menus that have been initialized
 * @author @scawful
 * 
 * @param dt 
 */
void CharacterState::updateDropdowns(const float& dt)
{
    for (auto &it : this->dropDownLists) 
    {
        it.second->update(this->mousePosView, dt);
    }
}

/**
 * @brief Update any TextBox objects that have been initialized
 * @authors @scawful @jmielc2
 * 
 */
void CharacterState::updateTextboxes() 
{
    for (auto &it : this->textboxes)
    {
        it.second->update(this->mousePosView, *this->sfEvent.get());
    }
}

/**
 * @brief Neutralize any active TextBox objects 
 * @authors @scawful @jmielc2
 * 
 */
void CharacterState::neutralizeTextboxes () 
{
    for (auto &it : this->textboxes)
    {
        it.second->neutralize();
    }
}

/**
 * @brief Cumulative update function for the CharacterState
 * @author @scawful
 * 
 * @param dt 
 */
void CharacterState::update(const float& dt) 
{
    this->updateMousePositions();
    this->updateInput(dt); 

    this->updateButtons();
    this->updateDropdowns(dt);
    this->updateTextboxes();
}

/**
 * @brief Render any Button objects to the sf::RenderTarget
 * @author @scawful
 * 
 * @param target 
 */
void CharacterState::renderButtons(sf::RenderTarget& target)
{
    for ( auto &it : this->buttons ) 
    {
        it.second->render(target);
    }
}

/**
 * @brief Render any DropDown objects to the sf::RenderTarget
 * @author @scawful
 * 
 * @param target 
 */
void CharacterState::renderDropdowns(sf::RenderTarget& target)
{
    for ( auto &it : this->dropDownLists )
    {
        it.second->render(target);
    }
}

/**
 * @brief Render any TextBox objects to the sf::RenderTarget
 * @author @scawful
 * 
 * @param target 
 */
void CharacterState::renderTextbox(sf::RenderTarget& target) 
{
    for (auto &it : this->textboxes)
    {
        it.second->render(target);
    }
}

/**
 * @brief Render the substates of the Character Creation Process
 * @author @scawful
 * 
 * @todo finish it
 * 
 * @param target 
 */
void CharacterState::renderSubStates(sf::RenderTarget& target)
{
    switch ( current_substate )
    {
        // into scene
        case 0: 
        {
            // Create the text for the title
            std::string terminal_text = "[root@awful ~]$ ./create_character -z\n\n\n\t\t\t\t\t\tProject Awful character creation v0.1\n\n\t\t\t\t\t\tClick the arrow below to proceed.";
            TextBlock title(terminal_text, &characterFont, sf::Color::White, 18, true);
            title.setPosition( SCREEN_WIDTH * 0.025 , SCREEN_HEIGHT * 0.025 );
            title.render(target);
            break;
        }
        // enter name 
        case 1:
        {
            std::string terminal_text = "*******************\n*-\t\t\t\t\t\t\t\t\t\t-*\n*  Create Character! *\n*-\t\t\t\t\t\t\t\t\t\t-*\n*******************\n";
            TextBlock title(terminal_text, &characterFont, sf::Color::White, 18, true);
            title.setPosition( SCREEN_WIDTH * 0.025 , SCREEN_HEIGHT * 0.025 );
            title.render(target);
            this->textboxes["CHARACTER_NAME"]->render(target);
            break;
        }
        // pick gender
        case 2:
        {
            this->dropDownLists["GENDER"]->render(target);
            break;
        }
        // class
        case 3:
        {
            this->dropDownLists["CLASS"]->render(target);
            break;
        }
        default: 
        {

        }
    }

    this->buttons["CONFIRM_BTN"]->render(target);
    this->buttons["BACK_BTN"]->render(target);
}

/**
 * @brief Cumulative render function for the CharacterState
 * @author @scawful
 * 
 * @param target 
 */
void CharacterState::render(sf::RenderTarget* target) 
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    this->renderSubStates(*target);
}
