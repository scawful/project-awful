#include "DungeonGenerator.hpp"

int DungeonGenerator::getRandomUnusedRoomID()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
    uniform_int_distribution<int> randomRoom(0, numRooms);
    int newID = randomRoom(rng);
    bool diffRoom = false;
    size_t n = roomTypesAssigned.size();

    while(!diffRoom) {
        if ( roomTypesAssigned.contains(newID) ) {
            newID = randomRoom(rng);
        } else {
            diffRoom = true;
        }
    }
    roomTypesAssigned.emplace(newID);
    return newID;
}

DungeonGenerator::DungeonGenerator( int difficulty, int minimum, int x, int y, int width, int height )
{
    this->roomID = 0;
    this->dungeonID = 0;
    this->minimumRoomSize = minimum;
    this->difficultyLevel = difficulty;
    this->numRoomsModifier = difficulty % 10;
}

DungeonGenerator::~DungeonGenerator()
{
    cout << "DungeonGenerator destroyed\n";
}

void DungeonGenerator::generateDungeon()
{
    // random-number engine used (Mersenne-Twister in this case)
    // using the std::chrono clock as the random seed engine, since mingw uses a fixed seed for std::random
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    uniform_int_distribution<int> randomNumRooms(0, difficultyLevel * 5); // guaranteed unbiased
    this->numRooms = randomNumRooms(rng);

    // initialize all the rooms 
    for ( int i = 0; i < numRooms; i++ ) {
        rooms.put(i, new Dungeon::Room(i));
    }

    int bossRoom = getRandomUnusedRoomID();
    rooms.at(bossRoom).setRoomType(Dungeon::RoomType::BOSS);

    int originRoom = getRandomUnusedRoomID();
    rooms.at(originRoom).setRoomType(Dungeon::RoomType::Origin);

    uniform_int_distribution<int> randomBinary(0,1);
    int hasMiniBoss = randomBinary(rng);
    
    if (hasMiniBoss) {
        int miniBossRoom = getRandomUnusedRoomID();
        rooms.at(miniBossRoom).setRoomType(Dungeon::RoomType::MINI_BOSS);
    }

    // randomize remaining rooms with nonspecial types 
    while ( roomTypesAssigned.size() != numRooms ) {
        uniform_int_distribution<int> randomRoomType(0, Dungeon::nRoomTypes);
        int newID = getRandomUnusedRoomID();
        rooms.at(newID).setRoomType(RoomType(randomRoomType(rng)));
    }

}

void DungeonGenerator::render(sf::RenderTarget& target)
{

}