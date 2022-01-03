#include "Dungeon.hpp"

// DUNGEON NAMESPACE
// TABLE OF CONTENTS 
// 1. TILE 
// 2. DOOR 
// 3. 


// ==============================================================================================================
//
//                                            TILE OBJECT DEFINITION 
//
// ==============================================================================================================

Dungeon::Tile::Tile()
{

}

Dungeon::Tile::~Tile()
{

}

sf::RectangleShape Dungeon::Tile::getTileRectangle()
{
    return this->tileRect;
}

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
    } else if ( type == TileType::DOOR_CLOSED ) {
        textureImage.loadFromFile("../assets/door_closed.png");
        tileTexture.loadFromImage(textureImage);
    } else if ( type == TileType::DOOR_OPEN ) {
        textureImage.loadFromFile("../assets/door_open.png");
        tileTexture.loadFromImage(textureImage);
    }
}

void Dungeon::Tile::setTileRectCoords( int top, int left )
{
    tileRect.setPosition( sf::Vector2f( top, left ) );
}

void Dungeon::Tile::setTileRectSize( int width, int height ) 
{
    tileRect.setSize( sf::Vector2f(width, height) );
}

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
 * 
 */
Dungeon::Door::Door(int x, int y, int dest)
{
    this->x = x;
    this->y = y;
    this->destinationRoom = dest;
    this->isClosed = true;
}

Dungeon::Door::~Door()
{
    
}

int Dungeon::Door::getDestinationRoom() {
    return destinationRoom;
}

sf::Vector2i Dungeon::Door::getPosition() {
    return sf::Vector2i(x,y);
}

bool Dungeon::Door::getIsClosed() {
    return isClosed;
}

void Dungeon::Door::setOpen()
{
    isClosed = false;
}

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
    uniform_int_distribution<int> randDoorLocation(1, width - 2);

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

    while ( numDoors != 0 ) {
        int x = randDoorLocation(rng);
        uniform_int_distribution<int> randomRoom(0, numSiblings - 1);
        tilesMatrix[x][0].setTileType(TileType::DOOR_CLOSED);
        doors.push_back( Door(x, 0, randomRoom(rng)) );
        numDoors--;
    }

}

/**
 * @brief Construct a new Dungeon:: Room:: Room object
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
 * 
 */
Dungeon::Room::~Room()
{
    destroyRoom();
}

/**
 * @brief Publicly available routine to clear the tiles matrix 
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
 * 
 */
void Dungeon::Room::createRoom() {
    initTiles();
}

/**
 * @brief Next Room Number to transition to as reported by update 
 * 
 * @return int 
 */
int Dungeon::Room::getNextRoomNumber() {
    return nextRoomNumber;
}

/**
 * @brief Set the Room Type which determines rooms random content set 
 * 
 * @param type 
 */
void Dungeon::Room::setRoomType( RoomType type )
{
    this->roomType = type;
}

/**
 * @brief get the players position and size from the outer layer for collission detection
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
 * 
 */
void Dungeon::Room::setRoomChangeHandshake()
{
    isChangingRoom = false;
}

/**
 * @brief reports if player is changing rooms or not 
 * 
 * @return true 
 * @return false 
 */
bool Dungeon::Room::changeRoom() {
    return isChangingRoom;
}

/**
 * @brief update the contents of the Dungeon room 
 * 
 */
void Dungeon::Room::updateRoom()
{
    for ( int i = 0; i < doors.size(); i++ ) {
        sf::Rect<float> playerRect;
        playerRect.top = playerPosition.x;
        playerRect.left = playerPosition.y;
        playerRect.width = playerSize.x;
        playerRect.height = playerSize.y;

        if ( tilesMatrix[doors[i].getPosition().x][doors[i].getPosition().y].getTileRectangle().getGlobalBounds().contains(playerPosition) ) 
        {
            tilesMatrix[doors[i].getPosition().x][doors[i].getPosition().y].setTileType(TileType::DOOR_OPEN);
            doors[i].setOpen();
            isChangingRoom = true;
            nextRoomNumber = doors[i].getDestinationRoom();
        } else {
            if (!doors[i].getIsClosed()) {
                tilesMatrix[doors[i].getPosition().x][doors[i].getPosition().y].setTileType(TileType::DOOR_CLOSED);
                doors[i].setOpen();
            }
        }
    }    
}

/**
 * @brief Render the non state entities of the room (tiles)
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


