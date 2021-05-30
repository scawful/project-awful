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
        Room *leftChild;
        Room *rightChild;
        Room *dungeon;
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

        Room* getDungeon()
        {
            return this->dungeon;
        }
        
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