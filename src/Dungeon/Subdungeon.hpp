#ifndef Subdungeon_hpp
#define Subdungeon_hpp

#include "../core.hpp"
#include "Room.hpp"

class Subdungeon
{
private:
    Room *room;
    Subdungeon *left_child;
    Subdungeon *right_child;
    Subdungeon *sibling;

public:
    int id, top, left, width, height;
    Subdungeon(int id, int top, int left, int width, int height);
    ~Subdungeon();

    void setLeftChild( Subdungeon *leftChild );
    void setRightChild( Subdungeon *rightChild );
    void setSibling( Subdungeon *sibling );
    void addRoom( Room *new_room );

    Subdungeon* getLeftChild()
    {
        return this->left_child;
    }

    Subdungeon* getRightChild()
    {
        return this->right_child;
    }

    Subdungeon* getSibling()
    {
        return this->sibling;
    }

    Room* getRoom()
    {
        return this->room;
    }

    bool isLeaf()
    {
        return (this->left_child != NULL && this->right_child != NULL);
    }

};

#endif