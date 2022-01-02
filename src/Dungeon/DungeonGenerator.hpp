#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"

class DungeonGenerator
{
private:
    int rootRoomX, rootRoomY, rootRoomW, rootRoomH;
    int difficultyLevel;
    int minimumRoomSize;
    int roomID, dungeonID;

    Dungeon::Room *rootRoom;
    vector<Dungeon::Room*> vectorRooms;
    vector<Dungeon::Room*> corridors;

public:
    void initRootRoom( int x, int y, int width, int height );

    DungeonGenerator( int difficulty, int minimum, int x, int y, int width, int height );
    ~DungeonGenerator();

    // Functions    
    void deleteDungeon( Dungeon::Room *room );
    bool splitRoom( Dungeon::Room *room );

    bool random_split( Dungeon::Room *room );

    void generateDungeon( Dungeon::Room *room );
    void generateCorridors( Dungeon::Room *room );
    void generateCorridorBetween( Dungeon::Room *left, Dungeon::Room *right );

    void render(sf::RenderTarget& target);

};

#endif
