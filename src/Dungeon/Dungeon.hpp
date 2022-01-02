#ifndef Dungeon_hpp
#define Dungeon_hpp

#include "../core.hpp"

namespace Dungeon
{
    /**
     * @brief Enum Bing Bong 
     * 
     */
    enum RoomType {
        EMPTY,
        SPARSE,
        ORIGIN,
        TREASURE,
        MERCHANT,
        MINI_BOSS,
        BOSS  
    };
    int nRoomTypes = 4;

    /**
     * @brief Object representing any room in a dungeon
     * 
     */
    class Room
    {
    private:
        // Base Values 
        int numDoors;
        int numEnemies;
        int numItems;
        RoomType roomType;   
        vector<Door> doors;


    public:
        int id, width, height;
        Room(int id);
        ~Room();
        
        Room* getDungeon() {
            return this->dungeon;
        }
        void setRoomType( RoomType type );
        void setDungeon( Room *dungeon );
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

    class Tile
    {
    private:
        sf::Texture tileTexture;
        sf::RectangleShape tileRect;

    public:
        Tile();
        bool canWalk;
    };

}

#endif