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
        TREASURE,
        MERCHANT,
        ORIGIN,
        MINI_BOSS,
        BOSS  
    };

    enum TileType {
        FLOOR, 
        WALL
    };

    class Tile
    {
    private:
        TileType tileType;
        sf::Texture tileTexture;
        sf::RectangleShape tileRect;

    public:
        Tile();
        ~Tile();

        void setTileType( TileType type );
        void setTileRectCoords( int top, int left );
        void setTileRectSize( int width, int height );
        void render( sf::RenderTarget& target );
    };

    class Door
    {
    private:
        sf::Texture graphics;

    public:
        Door();
        ~Door();
    };


    /**
     * @brief Object representing any room in a dungeon
     * 
     */
    class Room
    {
    private:
        // Base Values 
        int roomId;
        int numDoors;
        int numEnemies;
        int numItems;

        // Special Values 
        RoomType roomType;

        // Data Structures    
        vector<Dungeon::Door> doors;
        Tile **tilesMatrix;

        // Initializers
        void initTiles();

    public:
        int width, height;
        Room(int id);
        ~Room();
        
        void createRoom();
        void setRoomType( RoomType type );
        void drawRoom( sf::RenderTarget& target );
    };
}

#endif