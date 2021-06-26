#include "Dungeon.hpp"

// Room

Dungeon::Room::Room(int id, int top, int left, int width, int height)
{
    this->id = id;
    this->top = top;
    this->left = left;
    this->width = width;
    this->height = height;
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->dungeon = NULL;
    this->minimumRoomSize = 5;
    cout << this->id << " " << this->top << " " << this->left << " " << this->width  << " " << this->height << endl;
}

Dungeon::Room::~Room()
{
    if ( this->dungeon != NULL )
    {   
        delete this->dungeon;
        this->dungeon = NULL;
    }
}

void Dungeon::Room::setParent( Room *parent )
{
    this->parent = parent;
}

void Dungeon::Room::setDungeon( Room *dungeon )
{
    this->dungeon = dungeon;
}

void Dungeon::Room::setLeftChild(Room *leftChild)
{
    this->leftChild = leftChild;
}

void Dungeon::Room::setRightChild(Room *rightChild)
{
    this->rightChild = rightChild;
}

void Dungeon::Room::drawRoom( sf::RenderTarget& target )
{
    if ( this->leftChild != NULL && this->dungeon == NULL )
    {
        this->leftChild->drawRoom( target );
        this->rightChild->drawRoom( target );
    }
    else
    {
        sf::RectangleShape roomRect;
        roomRect.setPosition( sf::Vector2f( this->top, this->left ) ) ;
        roomRect.setSize( sf::Vector2f( this->height, this->width ) );
        roomRect.setFillColor( sf::Color::Black );
        roomRect.setFillColor( sf::Color( 200, 200, 200, 150 ) );
        roomRect.setOutlineThickness(3);
        roomRect.setOutlineColor( sf::Color::Red );
        target.draw(roomRect);
    }

}

// Door
Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}