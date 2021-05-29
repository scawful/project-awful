#include "DungeonGenerator.hpp"

void DungeonGenerator::initOriginRoom()
{
    rooms = new Dungeon::Room( this->top, this->left, this->width, this->height );
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator()
{
    this->top = 0;
    this->left = 0;
    this->width = this->maximumRoomSize;
    this->height = this->maximumRoomSize;
    this->allocatedRooms = alloc_size;
    this->usedRooms = 0;
    
    this->initOriginRoom();
}

DungeonGenerator::~DungeonGenerator()
{
    delete rooms;
    cout << "Origin Room deleted\n";
}

bool DungeonGenerator::splitRoom( Dungeon::Room *room )
{
    if ( room->getLeftChild() != NULL )
        return false;

    // horizontal
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());      // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> horizRand(0,1); // guaranteed unbiased
    int horizontal = horizRand(rng);

    int maximum = 0;
    if ( horizontal )
        maximum = this->height;
    else
        maximum = this->width;

    maximum -= this->minimumRoomSize;

    if ( maximum <= this->minimumRoomSize)
        return false;

    // split 
    uniform_int_distribution<int> splitRand(0,maximum); // guaranteed unbiased
    int split = splitRand(rng);

    if ( split < this->minimumRoomSize )
    {
        split = this->minimumRoomSize;
    }

    if ( horizontal )
    {
        room->setLeftChild( new Dungeon::Room( top, left, split, width ) );
        room->setRightChild( new Dungeon::Room( top + split, left, height - split, width ) );
    }
    else
    {
        room->setLeftChild( new Dungeon::Room( top, left, height, split ) );
        room->setRightChild( new Dungeon::Room( top, left + split, height, width - split ) );
    }
    
    return true;
}