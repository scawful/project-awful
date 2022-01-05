#ifndef Dungeon_hpp
#define Dungeon_hpp

#include "../core.hpp"
#include "../Actor/Player.hpp"

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
        DOOR_UPPER_CLOSED,
        DOOR_UPPER_OPEN
    };

    /**
     * @brief Tile Object Declaration 
     * 
     */
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

    /**
     * @brief Door Object Declaration 
     * 
     */
    class Door
    {
    private:
        int x, y;
        int doorId;
        int destinationRoom;
        bool isClosed;
        sf::Texture graphics;

    public:
        Door(int id, int destination, sf::Vector2i location);
        ~Door();

        int getDestinationRoom();
        sf::Vector2i getPosition();
        bool getIsClosed();
        void setOpen();
        void setClosed();
    };


    /**
     * @brief Room Object Declaration
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
        int nextRoomNumber;
        int numSiblings;
        bool isChangingRoom;

        // Positions 
        sf::Vector2f playerPosition;
        sf::Vector2f playerSize;

        // Special Values 
        RoomType roomType;

        // Data Structures    
        vector<Dungeon::Door> doors;

        // Connections between doors
        unordered_map<int, int> doorConnections;
        
        Tile **tilesMatrix;

        // Initializers
        void initTiles();
        void initDoors();

    public:
        int width, height;
        Room(int id, int width, int height, int numDoors, int numSiblings);
        ~Room();
        
        void destroyRoom();
        void createRoom();

        void addDoor( int id, int destination, sf::Vector2i location );

        // Accessors
        int getDoorConnection(int id);
        int getNextRoomNumber();
        int getNumDoors();

        // Modifiers
        void setRoomType( RoomType type );
        void setPlayerPosition( sf::Vector2f position, sf::Vector2f size );
        void setRoomChangeHandshake();

        bool changeRoom();
        void updateRoom();
        void drawRoom( sf::RenderTarget& target );
    };
}

#endif