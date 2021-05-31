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

    //
    // 
    class Room
    {
    private:
        int minimumRoomSize;
        Tile *tiles;
        Room *parent;
        Room *leftChild;
        Room *rightChild;
        Room *dungeon;

    public:
        int id, top, left, width, height;
        Room(int id, int top, int left, int width, int height);
        ~Room();
        

        bool isLeaf()
        {
            return this->leftChild == NULL && this->rightChild == NULL;
        }

        Room* getRoom()
        {
            if ( isLeaf() )
                return this->dungeon;

            if ( this->leftChild != NULL )
            {
                return this->leftChild;
            }

            if ( this->rightChild != NULL )
            {
                return this->rightChild;
            }
        }
        
        Room* getLeftChild()
        {
            return this->leftChild;
        }

        Room* getRightChild()
        {
            return this->rightChild;
        }

        Room* getDungeon()
        {
            return this->dungeon;
        }
        
        void setParent( Room *parent );
        void setDungeon( Room *dungeon );
        void setLeftChild( Room *leftChild );
        void setRightChild( Room *rightChild );

        void drawRoom( sf::RenderTarget& target );
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