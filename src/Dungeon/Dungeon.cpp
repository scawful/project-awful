#include "Dungeon.hpp"

// Room

Dungeon::Room::Room(int id, int top, int left, int width, int height)
{
    this->id = id;
    this->top = top;
    this->left = left;
    this->width = width;
    this->height = height;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->dungeon = NULL;

    this->maximumRoomSize = 128;
    this->minimumRoomSize = 32;
}

Dungeon::Room::~Room()
{
    this->leftChild = NULL;
    this->rightChild = NULL;
}

void Dungeon::Room::setRoomID( int id )
{
    this->roomID = id;
}

void DungeonGenerator::deleteDungeon( )
{
    if ( room == NULL ) 
        return;

    this->deleteDungeon( this->leftChild );
    this->deleteDungeon( this->rightChild );

    delete room;
}

bool DungeonGenerator::splitRoom( )
{
    if ( this->leftChild != NULL )
        return false;

    // horizontal
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> horizRand(0,1); // guaranteed unbiased
    auto horizontal = horizRand(rng);

    int maximum = 0;
    if ( horizontal )
        maximum = this->height - this->getMinimumRoomSize();
    else
        maximum = this->width - this->getMinimumRoomSize();

    if ( maximum <= this->getMinimumRoomSize() )
        return false;

    // split 
    uniform_int_distribution<int> splitRand(0,maximum); // guaranteed unbiased
    auto split = splitRand(rng);

    if ( split < this->getMinimumRoomSize() )
    {
        split = this->getMinimumRoomSize();
    }

    if ( horizontal )
    {
        cout << "Left Child: " << roomID << " " << top << " " << left << " " << split << " " << room->width << endl;
        this->leftChild = new Dungeon::Room( roomID, top, left, split, room->width );
        roomID++;

        cout << "Right Child: " << roomID << " " << top + split << " " << left << " " << room->height - split << " " << room->width << endl;
        this->rightChild = new Dungeon::Room( roomID, top + split, left, room->height - split, room->width );
        roomID++;
    }
    else
    {
        cout << "Left Child: " << roomID << " " << top << " " << left << " " << room->height << " " << split << endl;
        this->leftChild = new Dungeon::Room( roomID, top, left, room->height, split );
        roomID++;
        cout << "Right Child: " << roomID << " " << room->top << " " << left + split << " " << room->height << " " << room->width - split << endl;
        this->rightChild = new Dungeon::Room( roomID, top, left + split, room->height, room->width - split );
        roomID++;
    }
    
    return true;
}

void DungeonGenerator::generateDungeon( )
{
    if( this->leftChild != NULL ) 
    { 
        // recursively generate 
        this->generateDungeon( this->leftChild );
        this->generateDungeon( this->rightChild );
    } 
    else 
    { 
        random_device rd;     // only used once to initialise (seed) engine
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)

        // if leaf node, create a dungeon within the minimum size constraints
        uniform_int_distribution<int> dungeonTopRnd(0, height - getMinimumRoomSize() );
        uniform_int_distribution<int> dungeonLeftRnd(0, width - getMinimumRoomSize() );

        int dungeonTop = ( height - getMinimumRoomSize() <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( width - getMinimumRoomSize() <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), getMinimumRoomSize() );
        int dungeonWidth = max( dungeonWidthRnd(rng), getMinimumRoomSize() );
        
        cout << "Dungeon: " << dungeonID << " " << top + dungeonTop << " " << left + dungeonLeft << " " << dungeonHeight << " " << dungeonWidth << endl;
        dungeon = new Dungeon::Room( dungeonID, top + dungeonTop, left + dungeonLeft, dungeonHeight, dungeonWidth );
        dungeonRooms.push_back( room );
        dungeonID++;
    }
}



// Door

Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}