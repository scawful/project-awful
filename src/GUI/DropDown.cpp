#include "DropDown.hpp"

/**
 * @brief Construct a new Drop Down:: Drop Down object
 * @author @scawful
 * 
 * @todo Change the active element to be some sort of prompt 
 *       Update the styling to look better any less blocky 
 * 
 * @param position 
 * @param size 
 * @param font 
 * @param list 
 * @param numElements 
 * @param default_index 
 */
DropDown::DropDown(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string list[], unsigned numElements, const unsigned default_index)
    : font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
    this->activeElement = new Button(
                    sf::Vector2f( position.x, position.y ), 
                    sf::Vector2f( size.x, size.y ),
                    &this->font, list[default_index], 24, true,
                    sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                    sf::Color(0x42dd22cc), sf::Color(0x4af626cc), sf::Color(0x4af626cc));

    for (size_t i = 0; i < numElements; i++)
    {
        this->list.push_back( 
            new Button
            (
                sf::Vector2f( position.x, position.y + ( ( i + 1 ) * size.y ) ), 
                sf::Vector2f( size.x, size.y ),
                &this->font, list[i], 24, true, 
                sf::Color(245, 245, 245, 200), sf::Color(255, 255, 255, 250), sf::Color(240, 240, 240, 100),
                sf::Color(0x42dd22cc), sf::Color(0x4af626cc), sf::Color(0x4af626cc)
            )
         );
    }
    
}

/**
 * @brief Destroy the Drop Down:: Drop Down object
 * @author @scawful
 * 
 */
DropDown::~DropDown()
{
    delete this->activeElement;
    for(size_t i = 0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }
}

/**
 * @brief Set the dropdown boxes colors 
 * @author @scawful
 * 
 * @param text_idle 
 * @param text_hover 
 * @param text_active 
 * @param active 
 * @param idle 
 * @param hover 
 */
void DropDown::setColors( sf::Color text_idle, sf::Color text_hover, sf::Color text_active, sf::Color active, sf::Color idle, sf::Color hover )
{
    this->activeElement->assignColors(text_idle, text_hover, text_active, idle, active, hover);
    for ( auto buttons : list )
    {
        buttons->assignColors( text_idle, text_hover, text_active, idle, active, hover );
    }
}

/**
 * @brief Retrieve the current keytime 
 * @author @scawful
 * 
 * @return true 
 * @return false 
 */
const bool DropDown::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

/**
 * @brief Update the current keytime 
 * @author @scawful
 * 
 * @param dt 
 */
void DropDown::updateKeytime(const float& dt)
{
    if ( this->keytime < this->keytimeMax )
    {
        this->keytime += 10.f * dt;
    }
}

/**
 * @brief Cumulative update routine for the dropdown menu 
 * @author @scawful
 * 
 * @param mousePos 
 * @param dt 
 */
void DropDown::update(const sf::Vector2f &mousePos, const float& dt)
{
    this->updateKeytime(dt);
    this->activeElement->update(mousePos);
    
    // Show and hide list
    if (this->activeElement->isPressed() && this->getKeytime())
    {
        if (this->showList)
            this->showList = false;
        else
            this->showList = true;
    }
    
    // if list is activated 
    if (this->showList)
    {
        for (auto &i : this->list)
        {
            i->update(mousePos);
            
            // close the list and replace the active element with the selected
            if (i->isPressed() && this->getKeytime())
            {
                this->showList = false;
                this->activeElement->setString(i->getString());
            }
        }
    }
}

/**
 * @brief Cumulative render function for the dropdown menu
 * @author @scawful
 * 
 * @param target 
 */
void DropDown::render(sf::RenderTarget &target)
{
    this->activeElement->render(target);
    
    if ( this->showList ) 
    {
        for ( auto &i : this->list )
        {
            i->render(target);
        }
    }
}