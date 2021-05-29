#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"

static int alloc_size = 10;

class DungeonGenerator
{
private:
    int allocatedRooms, usedRooms;
    int roomID, dungeonID;

    Dungeon::Room *rootRoom;
    vector<Dungeon::Room*> vectorRooms;

public:
    void initOriginRoom();

    DungeonGenerator();
    ~DungeonGenerator();

    // Functions
    void deleteDungeon( Dungeon::Room *room );

    void render(sf::RenderTarget& target);

};

#endif
