#ifndef DungeonGenerator_hpp
#define DungeonGenerator_hpp

#include "Dungeon.hpp"
#include "Subdungeon.hpp"

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

    Subdungeon *root;
    vector<Subdungeon*> subdungeon_vector;

public:
    void initRootRoom( int x, int y, int width, int height );

    DungeonGenerator( int difficulty, int minimum, int x, int y, int width, int height );
    ~DungeonGenerator();

    // Functions    
    void deleteDungeon( Subdungeon *sub );
    bool splitRoom( Subdungeon *sub );

    bool random_split( Subdungeon *sub );

    void generateDungeon( Subdungeon *sub );
    void generateCorridors( Subdungeon *sub );
    void generateCorridorBetween( Subdungeon *left, Subdungeon *right );

    void render(sf::RenderTarget& target);

};

#endif
