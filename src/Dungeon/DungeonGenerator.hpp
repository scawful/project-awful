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

    // State Variables 
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

    // Accessors 
    sf::Vector2f getDungeonDimensions();
    void setPlayerPositionInDungeon( sf::Vector2f position, sf::Vector2f size );

    // Random Dungeon Generation 
    void generateDungeon();

    // Update routine
    void updateDungeon();

    // Render routine 
    void render(sf::RenderTarget& target);

};

#endif
