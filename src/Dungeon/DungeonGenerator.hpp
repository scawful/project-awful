#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"

class DungeonGenerator
{
private:
    int minimumRoomSize;
    int roomID, dungeonID;
    int dungeonCount;

    Dungeon::Room *rootRoom;
    vector<Dungeon::Room*> vectorRooms;
    vector<Dungeon::Room*> corridors;

public:
    void initOriginRoom();

    DungeonGenerator();
    ~DungeonGenerator();

    // Functions
    void deleteDungeon( Dungeon::Room *room );
    bool splitRoom( Dungeon::Room *room );
    void generateDungeon( Dungeon::Room *room );
    void generateCorridorBetween( Dungeon::Room *leftRoom, Dungeon::Room *rightRoom );

    void render(sf::RenderTarget& target);

};

#endif
