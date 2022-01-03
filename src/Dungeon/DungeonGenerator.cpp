#include "DungeonGenerator.hpp"

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

DungeonGenerator::DungeonGenerator( int difficulty )
{
    this->difficultyLevel = difficulty;
    this->numRoomsModifier = difficulty % 10;
    generateDungeon();
}

DungeonGenerator::~DungeonGenerator()
{
    for ( auto & eachRoom : rooms ) {
        delete eachRoom.second;
    }
    cout << "DungeonGenerator destroyed\n";
}

sf::Vector2f DungeonGenerator::getDungeonDimensions()
{
    return sf::Vector2f( rooms.at(currentRoomNumber)->width * 100, rooms.at(currentRoomNumber)->height * 100 );
}

void DungeonGenerator::setPlayerPositionInDungeon( sf::Vector2f position, sf::Vector2f size )
{
    rooms.at(currentRoomNumber)->setPlayerPosition( position, size );
}

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
        rooms.emplace(i, new Dungeon::Room(i));
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

    cout << "Creating Origin Room #" << currentRoomNumber << endl;
    rooms.at(currentRoomNumber)->createRoom();
}

void DungeonGenerator::updateDungeon() 
{
    rooms.at(currentRoomNumber)->updateRoom();
}

void DungeonGenerator::render(sf::RenderTarget& target)
{
    try {
        rooms.at(currentRoomNumber)->drawRoom(target);
    } catch ( const std::out_of_range & e ) {
        cout << e.what() << endl;
    }
}