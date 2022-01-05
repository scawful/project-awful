#include "DungeonGenerator.hpp"

/**
 * @brief Randomly chooses a room id that hasn't yet been used as a specific room type
 *        Prevents duplicate boss, mini-boss, origin, etc 
 * @author @scawful
 * 
 * @return int 
 */
int DungeonGenerator::getRandomUnusedRoomID()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
    uniform_int_distribution<int> randomRoom(0, numRooms - 1);
    int newID = randomRoom(rng);
    bool diffRoom = false;
    size_t n = roomTypesAssigned.size();

    while(!diffRoom) {
        if ( roomTypesAssigned.count(newID) != 0 ) {
            newID = randomRoom(rng);
        } else {
            diffRoom = true;
        }
    }
    roomTypesAssigned.emplace(newID);
    return newID;
}

/**
 * @brief Construct a new Dungeon Generator:: Dungeon Generator object
 * @author @scawful
 * 
 * @param difficulty 
 */
DungeonGenerator::DungeonGenerator(Player *player, int difficulty)
{
    this->player = player;
    this->difficultyLevel = difficulty;
    this->numRoomsModifier = difficulty % 10;
    generateDungeon();
}

/**
 * @brief Destroy the Dungeon Generator:: Dungeon Generator object
 * @author @scawful
 * 
 */
DungeonGenerator::~DungeonGenerator()
{
    for ( auto & eachRoom : rooms ) {
        eachRoom.second->destroyRoom();
        delete eachRoom.second;
    }
    cout << "DungeonGenerator destroyed\n";
}

/**
 * @brief Return real dimensions of dungeon
 * @author @scawful
 * 
 * @todo make the tile size a variable 
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f DungeonGenerator::getDungeonDimensions()
{
    return sf::Vector2f( rooms.at(currentRoomNumber)->width * 100, rooms.at(currentRoomNumber)->height * 100 );
}

/**
 * @brief Let the room know the position and size of the player 
 * @author @scawful
 * 
 * @todo Either make the size assignment a separate function OR 
 *       just pass a reference to the player object or player position to the room object
 *       not sure yet
 * 
 * @param position 
 * @param size 
 */
void DungeonGenerator::setPlayerPositionInDungeon( sf::Vector2f position, sf::Vector2f size )
{
    rooms.at(currentRoomNumber)->setPlayerPosition( position, size );
}

/**
 * @brief Generate the dungeon doors for each room
 * @author @scawful
 * 
 */
void DungeonGenerator::generateDungeonDoors()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for ( int i = 0; i < this->numRooms; i++ )
    {
        sf::Vector2i location;
        int doorId = 0;
        int width = rooms.at(i)->width;
        int height = rooms.at(i)->height;
        int numDoors = rooms.at(i)->getNumDoors();
        while ( numDoors != 0 ) 
        {
            // decide which wall to put the door on and generate its position 
            uniform_int_distribution<int> randomEdge(0,3);
            int edge = randomEdge(rng);
            
            if ( edge == 0 ) {
                uniform_int_distribution<int> randDoorLocation(1, width - 2);
                location.x = randDoorLocation(rng);
                location.y = 0;
            } else if ( edge == 1 ) {
                uniform_int_distribution<int> randDoorLocation(1, height - 2);
                location.x = width - 1; 
                location.y = randDoorLocation(rng);
            } else if ( edge == 2 ) {
                uniform_int_distribution<int> randDoorLocation(1, width - 2);
                location.x = randDoorLocation(rng);
                location.y = height - 1;
            } else if ( edge == 3 ) {
                uniform_int_distribution<int> randDoorLocation(1, height - 2);
                location.x = 0;
                location.y = randDoorLocation(rng);
            }

            // calculate the destination of this door and make sure it's not already connected to another door 
            bool isAlreadyConnected = true;
            uniform_int_distribution<int> randomRoom(0, numRooms - 1);
            while (isAlreadyConnected) {
                int doorDestinationId = randomRoom(rng);
                
                if ( rooms.at(i)->getDoorConnection(doorDestinationId) == -1  && doorDestinationId != i ) {
                    isAlreadyConnected = false;
                    rooms.at(i)->addDoor( doorId, doorDestinationId, edge, location );
                }
            }
            numDoors--;
        }
    }
}

/**
 * @brief Randomly generate the contents of the dungeon 
 * @author @scawful
 * 
 */
void DungeonGenerator::generateDungeon()
{
    // random-number engine used (Mersenne-Twister in this case)
    // using the std::chrono clock as the random seed engine, since mingw uses a fixed seed for std::random
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    uniform_int_distribution<int> randomNumRooms(4, difficultyLevel * 10); // guaranteed unbiased
    this->numRooms = randomNumRooms(rng);
    cout << "Creating " << numRooms << " rooms" << endl;

    // initialize all the rooms 
    for ( int i = 0; i < numRooms; i++ ) {
        uniform_int_distribution<int> randomDimension(5, difficultyLevel * 10); // guaranteed unbiased
        uniform_int_distribution<int> randomNumDoors(1,3);
        rooms.emplace(i, new Dungeon::Room(i, randomDimension(rng), randomDimension(rng), randomNumDoors(rng), numRooms) );
    }

    int bossRoom = getRandomUnusedRoomID();
    try {
        rooms.at(bossRoom)->setRoomType(Dungeon::RoomType::BOSS);
    } catch ( const exception & e ) {
        cout << "Boss Room Exception: " << e.what() << endl;
    }

    int originRoom = getRandomUnusedRoomID();
    try {
        rooms.at(originRoom)->setRoomType(Dungeon::RoomType::ORIGIN);
    } catch ( const exception & e ) {
        cout << "Origin Room Exception: " << e.what() << endl;
    }
    this->currentRoomNumber = originRoom;

    uniform_int_distribution<int> randomBinary(0,1);
    int hasMiniBoss = randomBinary(rng);
    
    if (hasMiniBoss) {
        int miniBossRoom = getRandomUnusedRoomID();
        try {
            rooms.at(miniBossRoom)->setRoomType(Dungeon::RoomType::MINI_BOSS);
        } catch ( const exception & e ) {
            cout << "Mini Boss Room Exception: " << e.what() << endl;
        }
    }

    // randomize remaining rooms with nonspecial types 
    while ( roomTypesAssigned.size() != numRooms - 1 ) {
        uniform_int_distribution<int> randomRoomType(0, 4);
        int newID = getRandomUnusedRoomID();
        rooms.at(newID)->setRoomType(Dungeon::RoomType(randomRoomType(rng)));
    }

    // Creating all the rooms and their tiles 
    for ( auto & eachRoom : rooms ) {
        eachRoom.second->createRoom();
    }
    generateDungeonDoors();
}

/**
 * @brief Update the contents of the current room in the dungeon 
 *        Change rooms when using a door 
 * @author @scawful
 * 
 */
void DungeonGenerator::updateDungeon() 
{
    rooms.at(currentRoomNumber)->updateRoom();
    
    // player is at a door and can move to the next room 
    if ( rooms.at(currentRoomNumber)->changeRoom() ) {
        rooms.at(currentRoomNumber)->setRoomChangeHandshake();
        currentRoomNumber = rooms.at(currentRoomNumber)->getNextRoomNumber();
    }
}

/**
 * @brief Render the contents of the current room in the dungeon
 * @author @scawful
 * 
 * @param target 
 */
void DungeonGenerator::render(sf::RenderTarget& target)
{
    try {
        rooms.at(currentRoomNumber)->drawRoom(target);
    } catch ( const std::out_of_range & e ) {
        cout << e.what() << endl;
    }
}