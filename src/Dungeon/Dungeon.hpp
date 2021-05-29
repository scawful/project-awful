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
        Tile *tiles;
        Room *leftChild;
        Room *rightChild;
        sf::RectangleShape roomShape;

    public:
        Room(int top, int left, int width, int height);
        ~Room();

        Room* getLeftChild()
        {
            return leftChild;
        }

        void setLeftChild(Room *leftChild)
        {
            this->leftChild = leftChild;
        }

        void setRightChild(Room *rightChild)
        {
            this->rightChild = rightChild;
        }

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