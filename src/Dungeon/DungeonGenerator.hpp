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
    
    // Boolean 
    bool isTransitioning;

    // Modifiers
    double numRoomsModifier;

    // Data Structures 
    std::unordered_map<int, Dungeon::Room*> rooms;
    std::set<int> roomTypesAssigned;

    // sfml 
    sf::Text debugText;
    sf::Vector2f playerPosition;

    // Helper
    int getRandomUnusedRoomID();

public:
    DungeonGenerator( int difficulty );
    ~DungeonGenerator();

    // Functions    
    sf::Vector2f getDungeonDimensions();
    void setPlayerPositionInDungeon( sf::Vector2f position, sf::Vector2f size );
    void generateDungeon();

    void updateDungeon();
    void render(sf::RenderTarget& target);

};

#endif
