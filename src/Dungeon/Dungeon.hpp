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
        int roomID;
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

        int getRoomID()
        {
            return this->roomID;
        }

        void setRoomID( int id );

        void drawRoom( sf::RenderTarget& target );
        bool splitRoom();
        void generateDungeon();

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