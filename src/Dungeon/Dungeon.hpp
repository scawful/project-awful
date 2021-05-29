#ifndef Dungeon_hpp
#define Dungeon_hpp

#include "../core.hpp"

namespace Dungeon
{
    class Tile
    {
    private:
        sf::Texture tileTexture;
        sf::RectangleShape tileRect;

    public:
        Tile();
        bool canWalk;

    };

    class Room
    {
    private:
        int roomID;
        Tile *tiles;
        Room *leftChild;
        Room *rightChild;
        sf::RectangleShape roomShape;

    public:
        Room(int id, int top, int left, int width, int height);
        ~Room();
        int id, top, left, width, height;

        Room* getLeftChild()
        {
            return this->leftChild;
        }

        Room* getRightChild()
        {
            return this->rightChild;
        }

        int getRoomID()
        {
            return this->roomID;
        }

        void setRoomID( int id );
        void setLeftChild( Room *leftChild );
        void setRightChild( Room *rightChild );

        Room& operator =(const Room &t)
        {
            return *this;
        } 

    };


    class Door
    {
    private:
        sf::Texture graphics;

    public:
        Door();
        virtual ~Door();

    };

}

#endif