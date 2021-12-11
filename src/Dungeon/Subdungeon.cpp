#include "Subdungeon.hpp"

Subdungeon::Subdungeon(int id, int top, int left, int width, int height)
{
    this->id = id;
    this->top = top;
    this->left = left;
    this->width = width;
    this->height = height;
    this->left_child = NULL;
    this->right_child = NULL;
    this->sibling = NULL;
}

void Subdungeon::setLeftChild( Subdungeon *leftChild )
{
    this->left_child = leftChild;
}

void Subdungeon::setRightChild( Subdungeon *rightChild )
{
    this->left_child = rightChild;
}

void Subdungeon::setSibling( Subdungeon *sibling )
{
    this->sibling = sibling;
}

void Subdungeon::addRoom( Room *new_room )
{
    this->room = new_room;
}