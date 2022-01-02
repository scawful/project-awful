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
    int numRooms;
    int difficultyLevel;
    int currentRoomNumber;
    DungeonType dungeonType;    
    
    // Modifiers
    double numRoomsModifier;

    // Data Structures 
    std::unordered_map<int, Dungeon::Room*> rooms;
    std::set<int> roomTypesAssigned;

    // sfml 
    sf::Text debugText;

    // Helper
    int getRandomUnusedRoomID();

public:
    DungeonGenerator( int difficulty );
    ~DungeonGenerator();

    // Functions    
    void generateDungeon();
    void render(sf::RenderTarget& target);

};

#endif
