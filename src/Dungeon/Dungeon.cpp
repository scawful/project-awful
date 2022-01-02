#include "Dungeon.hpp"

/**
 * @brief Construct a new Dungeon:: Room:: Room object
 * 
 * @param id 
 */
Dungeon::Room::Room(int id)
{
    this->id = id;
    this->dungeon = NULL;
    cout << "Room #" << id << " initialized\n"; 
}

/**
 * @brief Destroy the Dungeon:: Room:: Room object
 * 
 */
Dungeon::Room::~Room()
{
    if ( this->dungeon != NULL )
    {   
        delete this->dungeon;
        this->dungeon = NULL;
    }
}

/**
 * @brief Set the Room Type which determines rooms random content set 
 * 
 * @param type 
 */
void Dungeon::Room::setRoomType( RoomType type )
{
    this->roomType = type;
}

void Dungeon::Room::setDungeon( Room *dungeon )
{
    this->dungeon = dungeon;
}

void Dungeon::Room::drawRoom( sf::RenderTarget& target )
{

    sf::RectangleShape roomRect;
    roomRect.setPosition( sf::Vector2f( 0, 0 ) ) ;
    roomRect.setSize( sf::Vector2f( this->height, this->width ) );
    roomRect.setFillColor( sf::Color::Black );
    roomRect.setFillColor( sf::Color( 200, 200, 200, 150 ) );
    roomRect.setOutlineThickness(3);
    roomRect.setOutlineColor( sf::Color::Red );
    target.draw(roomRect);
}

// Door
Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}