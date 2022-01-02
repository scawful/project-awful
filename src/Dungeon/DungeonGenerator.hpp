#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"

class DungeonGenerator
{
private:

    enum DungeonType {
        BASIC,
        INFESTED,
    };

    // Base Values 
    int difficultyLevel;
    int numRooms;
    DungeonType dungeonType;    
    
    // Modifiers
    double numRoomsModifier;

    // Data Structures 
    std::unordered_map<int, Dungeon::Room> rooms;
    std::set<int> roomTypesAssigned;

    // Helper
    int getRandomUnusedRoomID();

public:
    DungeonGenerator( int difficulty, int minimum, int x, int y, int width, int height );
    ~DungeonGenerator();

    // Functions    
    void generateDungeon();
    void render(sf::RenderTarget& target);

};

#endif
