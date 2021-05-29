#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"

static int alloc_size = 10;

class DungeonGenerator
{
private:
    int maximumRoomSize;
    int minimumRoomSize;
    int minimumDimension;
    int allocatedRooms, usedRooms;
    int top, left, width, height;
    int roomID;

    Dungeon::Room *rootRoom;
    vector<Dungeon::Room*> vectorRooms;

public:
    void initOriginRoom();

    DungeonGenerator();
    ~DungeonGenerator();

    // Functions
    void deleteDungeon( Dungeon::Room *room );
    bool splitRoom( Dungeon::Room *room );
    void generateDungeon( Dungeon::Room *room );

    void render(sf::RenderTarget& target);

};

#endif
