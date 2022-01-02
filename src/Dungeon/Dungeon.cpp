#include "Dungeon.hpp"

void Dungeon::Room::initTiles() 
{
    try {
        tilesMatrix = new Tile*[height];
        for ( int i = 0; i < height; i++ ) {
            tilesMatrix[i] = new Tile[width];
        }
    } catch ( const exception & e ) {
        cout << e.what() << endl;
    }

    int defaultTileSize = 100;
    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            tilesMatrix[i][j].setTileRectCoords( i * defaultTileSize, j * defaultTileSize );
            tilesMatrix[i][j].setTileRectSize( defaultTileSize, defaultTileSize );
            if ( i == 0 || j == 0 || i == width - 1 || j == height - 1 ) {
                tilesMatrix[i][j].setTileType(TileType::WALL);
            } else {
                tilesMatrix[i][j].setTileType(TileType::FLOOR);
            }
        }
    }
}

/**
 * @brief Construct a new Dungeon:: Room:: Room object
 * 
 * @param id 
 */
Dungeon::Room::Room(int id)
{
    this->roomId = id;
    this->height = 10;
    this->width = 10;
    cout << "Room #" << id << " initialized\n"; 
}

/**
 * @brief Destroy the Dungeon:: Room:: Room object
 * 
 */
Dungeon::Room::~Room()
{
    for(int i = 0; i < height; ++i) {
        delete [] tilesMatrix[i];
    }
    delete [] tilesMatrix;
    tilesMatrix = nullptr;
}

void Dungeon::Room::createRoom() {
    initTiles();
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

void Dungeon::Room::drawRoom( sf::RenderTarget& target )
{
    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            tilesMatrix[i][j].render(target);
        }
    }

    // sf::RectangleShape roomRect;
    // roomRect.setPosition( sf::Vector2f( 0, 0 ) ) ;
    // roomRect.setSize( sf::Vector2f( this->height, this->width ) );
    // roomRect.setFillColor( sf::Color::Black );
    // roomRect.setFillColor( sf::Color( 200, 200, 200, 150 ) );
    // roomRect.setOutlineThickness(3);
    // roomRect.setOutlineColor( sf::Color::Red );
    // target.draw(roomRect);
}

// =====================================================================

/**
 * @brief Construct a new Dungeon:: Door:: Door object
 * 
 */
Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}


// =====================================================================

Dungeon::Tile::Tile()
{

}

Dungeon::Tile::~Tile()
{

}

void Dungeon::Tile::setTileType( TileType type )
{
    this->tileType = type;
    if ( type == TileType::FLOOR ) {
        tileRect.setFillColor(sf::Color::White );
        tileRect.setOutlineThickness(3);
        tileRect.setOutlineColor( sf::Color::Red );
    } else if ( type == TileType::WALL ) {
        tileRect.setFillColor(sf::Color::Black );
        tileRect.setOutlineThickness(3);
        tileRect.setOutlineColor( sf::Color::Green );
        
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
    target.draw(tileRect);
}