#include "Dungeon.hpp"

// DUNGEON NAMESPACE
// TABLE OF CONTENTS 
// 1. TILE 
// 2. DOOR 
// 3. ROOM 
//

// ==============================================================================================================
//
//                                            TILE OBJECT DEFINITION 
//
// ==============================================================================================================

/**
 * @brief Construct a new Dungeon:: Tile:: Tile object
 * @author @scawful
 * 
 */
Dungeon::Tile::Tile()
{

}

/**
 * @brief Destroy the Dungeon:: Tile:: Tile object
 * 
 */
Dungeon::Tile::~Tile()
{
    
}

/**
 * @brief Accesses the RectangleShape object for the tile 
 * @author @scawful
 * 
 * @return sf::RectangleShape 
 */
sf::RectangleShape Dungeon::Tile::getTileRectangle()
{
    return this->tileRect;
}

/**
 * @brief Assign graphics to the sf::Texture object 
 * @author @scawful
 * 
 * @param type 
 */
void Dungeon::Tile::setTileType( TileType type )
{
    this->tileType = type;
    sf::Image textureImage;
    if ( type == TileType::FLOOR ) {
        textureImage.loadFromFile("../assets/floor_gray.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_TOP || type == TileType::WALL_BOTTOM ) {
        textureImage.loadFromFile("../assets/wall_top.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_UPPER_LEFT_CORNER ) {
        textureImage.loadFromFile("../assets/wall_top_left_corner.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_UPPER_RIGHT_CORNER ) {
        textureImage.loadFromFile("../assets/wall_top_right_corner.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_LOWER_LEFT_CORNER ) {
        textureImage.loadFromFile("../assets/wall_bottom_left_corner.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_LOWER_RIGHT_CORNER ) {
        textureImage.loadFromFile("../assets/wall_bottom_right_corner.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_LEFT ) {
        textureImage.loadFromFile("../assets/wall_left.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::WALL_RIGHT ) {
        textureImage.loadFromFile("../assets/wall_right.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::DOOR_UPPER_CLOSED ) {
        textureImage.loadFromFile("../assets/door_closed.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::DOOR_UPPER_OPEN ) {
        textureImage.loadFromFile("../assets/door_open.png");
        tileTexture.loadFromImage(textureImage);
    }
}

/**
 * @brief Assign tiles position 
 * @author @scawful
 * 
 * @param top 
 * @param left 
 */
void Dungeon::Tile::setTileRectCoords( int top, int left )
{
    tileRect.setPosition( sf::Vector2f( top, left ) );
}

/**
 * @brief Assign tiles scale 
 * @author @scawful
 * 
 * @param width 
 * @param height 
 */
void Dungeon::Tile::setTileRectSize( int width, int height ) 
{
    tileRect.setSize( sf::Vector2f(width, height) );
}

/**
 * @brief Render the sf::Texture object to the screen 
 * @author @scawful
 * 
 * @param target 
 */
void Dungeon::Tile::render( sf::RenderTarget& target )
{
    tileRect.setTexture(&tileTexture);
    target.draw(tileRect);
}

// ==============================================================================================================
// 
//                                          DOOR OBJECT DEFINITION 
//
// ==============================================================================================================

/**
 * @brief Construct a new Dungeon:: Door:: Door object
 * @author @scawful 
 * 
 */
Dungeon::Door::Door(int id, int destination, sf::Vector2i location)
{
    this->doorId = id;
    this->x = location.x;
    this->y = location.y;
    this->destinationRoom = destination;
    this->isClosed = true;
}

/**
 * @brief Destroy the Dungeon:: Door:: Door object
 * @author @scawful
 * 
 */
Dungeon::Door::~Door()
{
    
}

/**
 * @brief Return id of the next destination room 
 * 
 * @return int 
 */
int Dungeon::Door::getDestinationRoom() 
{
    return destinationRoom;
}

/**
 * @brief Return the position of the door itself 
 * 
 * @return sf::Vector2i 
 */
sf::Vector2i Dungeon::Door::getPosition() 
{
    return sf::Vector2i(x,y);
}

/**
 * @brief Check if the door is closed or not 
 * @author @scawful
 * 
 * @return true 
 * @return false 
 */
bool Dungeon::Door::getIsClosed() {
    return isClosed;
}

/**
 * @brief Modifier for door state 
 * @author @scawful
 * 
 */
void Dungeon::Door::setOpen()
{
    isClosed = false;
}

/**
 * @brief Modifier for the door state 
 * @author @scawful
 * 
 */
void Dungeon::Door::setClosed()
{
    isClosed = true;
}

// ==============================================================================================================
//
//                                          ROOM OBJECT DEFINITION 
//
// ==============================================================================================================

/**
 * @brief Assign the different tile types to the matrix 
 * @author @scawful
 * 
 * @todo verify consistent connections between doors 
 * @todo add left, right, and bottom door connections 
 * 
 */
void Dungeon::Room::initTiles() 
{
    try {
        tilesMatrix = new Tile*[width];
        for ( int i = 0; i < width; i++ ) {
            tilesMatrix[i] = new Tile[height];
        }
    } catch ( const exception & e ) {
        cout << e.what() << endl;
    }

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    int defaultTileSize = 100;
    for ( int i = 0; i < width; i++ ) {
        for ( int j = 0; j < height; j++ ) {
            tilesMatrix[i][j].setTileRectCoords( i * defaultTileSize, j * defaultTileSize );
            tilesMatrix[i][j].setTileRectSize( defaultTileSize, defaultTileSize );

            if ( i == 0 ) {
                if ( j == 0 ) {
                    tilesMatrix[i][j].setTileType(TileType::WALL_UPPER_LEFT_CORNER);
                } else if ( j == height - 1 ) {
                    tilesMatrix[i][j].setTileType(TileType::WALL_LOWER_LEFT_CORNER); 
                } else {
                    tilesMatrix[i][j].setTileType(TileType::WALL_LEFT);
                }

            } else if (i == width - 1) {
                if ( j == 0 ) {
                    tilesMatrix[i][j].setTileType(TileType::WALL_UPPER_RIGHT_CORNER); 
                } else if ( j == height - 1 ) {
                    tilesMatrix[i][j].setTileType(TileType::WALL_LOWER_RIGHT_CORNER);
                } else {
                    tilesMatrix[i][j].setTileType(TileType::WALL_RIGHT);
                }
            } else if ( j == 0 ) {
                tilesMatrix[i][j].setTileType(TileType::WALL_TOP);
            } else if ( j == height - 1 ) {
                tilesMatrix[i][j].setTileType(TileType::WALL_BOTTOM);
            } else {
                tilesMatrix[i][j].setTileType(TileType::FLOOR);
            }
        }
    }
}

/**
 * @brief Construct a new Dungeon:: Room:: Room object
 * @author @scawful
 * 
 * @param id 
 */
Dungeon::Room::Room(int id, int width, int height, int numDoors, int numSiblings)
{
    this->roomId = id;
    this->height = height;
    this->width = width;
    this->numDoors = numDoors;
    this->numSiblings = numSiblings;
    this->tilesMatrix = nullptr;
    isChangingRoom = false;
    cout << "Room #" << id << " initialized\n"; 
}

/**
 * @brief Destroy the Dungeon:: Room:: Room object
 * @author @scawful
 * 
 */
Dungeon::Room::~Room()
{
    destroyRoom();
}

/**
 * @brief Publicly available routine to clear the tiles matrix 
 * @author @scawful
 * 
 */
void Dungeon::Room::destroyRoom()
{
    if ( tilesMatrix != nullptr ) {
        for(int i = 0; i < width; i++) {
            delete [] tilesMatrix[i];
        }
        delete [] tilesMatrix;
        tilesMatrix = nullptr;
    }
}

/**
 * @brief Publicly available function for building the Room 
 * @author @scawful
 * 
 */
void Dungeon::Room::createRoom() 
{
    initTiles();
}

/**
 * @brief Add a door to the room 
 * 
 * @param id 
 * @param destination 
 * @param location 
 */
void Dungeon::Room::addDoor( int id, int destination, int direction, sf::Vector2i location )
{
    doors.push_back(Door( id, destination, location ));
    if ( direction == 0 ) {
        tilesMatrix[location.x][location.y].setTileType(TileType::DOOR_UPPER_CLOSED);
    } else if ( direction == 1 ) {
        tilesMatrix[location.x][location.y].setTileType(TileType::DOOR_RIGHT_CLOSED);
    } else if ( direction == 2 ) {
        tilesMatrix[location.x][location.y].setTileType(TileType::DOOR_LOWER_CLOSED);
    } else if ( direction == 3 ) {
        tilesMatrix[location.x][location.y].setTileType(TileType::DOOR_LEFT_CLOSED);
    }
    doorConnections.emplace( id, destination );
}

/**
 * @brief 
 * 
 * @param id 
 * @return int 
 */
int Dungeon::Room::getDoorConnection(int id)
{
    if ( doorConnections.count(id) != 0 ) {
        return doorConnections[id];
    }

    return -1;
}

/**
 * @brief Next Room Number to transition to as reported by update 
 * @author @scawful
 * 
 * @return int 
 */
int Dungeon::Room::getNextRoomNumber() {
    return nextRoomNumber;
}

/**
 * @brief 
 * 
 * @return int 
 */
int Dungeon::Room::getNumDoors() 
{
    return this->numDoors;
}

/**
 * @brief Set the Room Type which determines rooms random content set 
 * @author @scawful
 * 
 * @param type 
 */
void Dungeon::Room::setRoomType( RoomType type )
{
    this->roomType = type;
}

/**
 * @brief get the players position and size from the outer layer for collission detection
 * @author @scawful
 * 
 * @param position 
 * @param size 
 */
void Dungeon::Room::setPlayerPosition( sf::Vector2f position, sf::Vector2f size )
{
    this->playerPosition = position;
    this->playerSize = size;
}

/**
 * @brief tell the room we're done changing rooms 
 * @author @scawful
 * 
 */
void Dungeon::Room::setRoomChangeHandshake()
{
    isChangingRoom = false;
}

/**
 * @brief reports if player is changing rooms or not 
 * @author @scawful
 * 
 * @return true 
 * @return false 
 */
bool Dungeon::Room::changeRoom() {
    return isChangingRoom;
}

/**
 * @brief update the contents of the Dungeon room 
 * @author @scawful
 * 
 */
void Dungeon::Room::updateRoom()
{
    for ( int i = 0; i < doors.size(); i++ ) {
        sf::Rect<float> playerRect;
        playerRect.top = playerPosition.x;
        playerRect.left = playerPosition.y;
        playerRect.width = playerSize.;
        playerRect.height = playerSize.y;

        if (tilesMatrix[doors[i].getPosition().x][doors[i].getPosition().y].getTileRectangle().getGlobalBounds().contains(playerPosition)) 
        {
            tilesMatrix[doors[i].getPosition().x][doors[i].getPosition().y].setTileType(TileType::DOOR_UPPER_OPEN);
            doors[i].setOpen();
            isChangingRoom = true;
            nextRoomNumber = doors[i].getDestinationRoom();
        } else {
            if (!doors[i].getIsClosed()) {
                tilesMatrix[doors[i].getPosition().x][doors[i].getPosition().y].setTileType(TileType::DOOR_UPPER_CLOSED);
                doors[i].setOpen();
            }
        }
    }    
}

/**
 * @brief Render the non state entities of the room (tiles)
 * @author @scawful
 * 
 * @param target 
 */
void Dungeon::Room::drawRoom( sf::RenderTarget& target )
{
    for ( int i = 0; i < width; i++ ) {
        for ( int j = 0; j < height; j++ ) {
            tilesMatrix[i][j].render(target);
        }
    }
}