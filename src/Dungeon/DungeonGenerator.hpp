#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"

static int alloc_size = 10;

class DungeonGenerator
{
private:
    const static int maximumRoomSize = 256;
    const static int minimumRoomSize = 16;
    const static int minimumDimension = 4;
    int allocatedRooms, usedRooms;
    int top, left, width, height;

    Dungeon::Room *rooms;

public:
    void initOriginRoom();

    DungeonGenerator();
    ~DungeonGenerator();

    // Functions
    bool splitRoom( Dungeon::Room *room );
    void generateDungeons();

};

#endif
