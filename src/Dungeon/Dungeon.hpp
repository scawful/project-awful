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
        WALL_TOP,
        WALL_BOTTOM,
        WALL_LEFT,
        WALL_RIGHT,
        WALL_UPPER_LEFT_CORNER,
        WALL_UPPER_RIGHT_CORNER,
        WALL_LOWER_LEFT_CORNER,
        WALL_LOWER_RIGHT_CORNER,
        DOOR_CLOSED,
        DOOR_OPEN
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

        sf::RectangleShape getTileRectangle();
        void setTileType( TileType type );
        void setTileRectCoords( int top, int left );
        void setTileRectSize( int width, int height );
        void render( sf::RenderTarget& target );
    };

    class Door
    {
    private:
        int x, y;
        bool isClosed;
        sf::Texture graphics;

    public:
        Door(int x, int y);
        ~Door();

        sf::Vector2i getPosition();
        bool getIsClosed();
        void setOpen();
        void setClosed();
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

        // Positions 
        sf::Vector2f playerPosition;
        sf::Vector2f playerSize;

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
        void setPlayerPosition( sf::Vector2f position, sf::Vector2f size );

        void updateRoom();
        void drawRoom( sf::RenderTarget& target );
    };
}

#endif