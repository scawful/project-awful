#include "Dungeon.hpp"

// Room

Dungeon::Room::Room(int id, int top, int left, int width, int height)
{
    this->id = id;
    this->top = top;
    this->left = left;
    this->width = width;
    this->height = height;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

Dungeon::Room::~Room()
{
    delete this->leftChild;
    delete this->rightChild;
}

void Dungeon::Room::setRoomID( int id )
{
    this->roomID = id;
}

void Dungeon::Room::setLeftChild(Room *leftChild)
{
    this->leftChild = leftChild;
}

void Dungeon::Room::setRightChild(Room *rightChild)
{
    this->rightChild = rightChild;
}

// Door

Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}