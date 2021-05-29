#include "DungeonGenerator.hpp"

void DungeonGenerator::initOriginRoom()
{
    rootRoom = new Dungeon::Room( this->roomID, this->top, this->left, this->width, this->height );
    roomID++;
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator()
{
    this->maximumRoomSize = 256 * 2;
    this->minimumRoomSize = 64;
    this->minimumDimension = 4;

    this->top = 0;
    this->left = 0;
    this->width = this->maximumRoomSize;
    this->height = this->maximumRoomSize;
    this->allocatedRooms = alloc_size;
    this->usedRooms = 0;
    this->roomID = 0;

    this->initOriginRoom();
    vectorRooms.push_back( rootRoom );

    for ( int i = 0; i < 30; i++ )
    {
        random_device rd;     // only used once to initialise (seed) engine
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
        uniform_int_distribution<int> splitRand(0, vectorRooms.size() - 1 ); // guaranteed unbiased
        auto splitID = splitRand(rng);

        Dungeon::Room *roomToSplit = vectorRooms[splitID];
        if ( this->splitRoom( roomToSplit ) )
        {
            vectorRooms.push_back( roomToSplit->getLeftChild() );
            vectorRooms.push_back( roomToSplit->getRightChild() );
        }
    }

    this->generateDungeon( rootRoom );
}

DungeonGenerator::~DungeonGenerator()
{
    deleteDungeon( rootRoom );
}

void DungeonGenerator::deleteDungeon( Dungeon::Room *room )
{
    if ( room == NULL ) 
        return;

    this->deleteDungeon( room->getLeftChild() );
    this->deleteDungeon( room->getRightChild() );

    delete room;
}

bool DungeonGenerator::splitRoom( Dungeon::Room *room )
{
    if ( room->getLeftChild() != NULL )
        return false;

    // horizontal
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> horizRand(0,1); // guaranteed unbiased
    auto horizontal = horizRand(rng);

    int maximum = 0;
    if ( horizontal )
        maximum = this->height;
    else
        maximum = this->width;

    maximum -= this->minimumRoomSize;

    if ( maximum <= this->minimumRoomSize )
        return false;

    // split 
    uniform_int_distribution<int> splitRand(0,maximum); // guaranteed unbiased
    auto split = splitRand(rng);

    if ( split < this->minimumRoomSize )
    {
        split = this->minimumRoomSize;
    }

    if ( horizontal )
    {
        cout << "Left Child: " << roomID << " " << top << " " << left << " " << split << " " << width << endl;
        room->setLeftChild( new Dungeon::Room( roomID, top, left, split, width ) );
        roomID++;
        cout << "Right Child: " << roomID << " " << top + split << " " << left << " " << height - split << " " << width << endl;
        room->setRightChild( new Dungeon::Room( roomID, top + split, left, height - split, width ) );
        roomID++;
    }
    else
    {
        cout << "Left Child: " << roomID << " " << top << " " << left << " " << height << " " << split << endl;
        room->setLeftChild( new Dungeon::Room( roomID, top, left, height, split ) );
        roomID++;
        cout << "Right Child: " << roomID << " " << top << " " << left + split << " " << height << " " << width - split << endl;
        room->setRightChild( new Dungeon::Room( roomID, top, left + split, height, width - split ) );
        roomID++;
    }
    
    return true;
}

void DungeonGenerator::generateDungeon( Dungeon::Room *room )
{
    if( room->getLeftChild() != NULL ) 
    { 
        // recursively generate 
        this->generateDungeon( room->getLeftChild() );
        this->generateDungeon( room->getRightChild() );
    } 
    else 
    { 
        random_device rd;     // only used once to initialise (seed) engine
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)

        // if leaf node, create a dungeon within the minimum size constraints
        uniform_int_distribution<int> dungeonTopRnd(0, this->height - this->minimumRoomSize );
        uniform_int_distribution<int> dungeonLeftRnd(0, this->width - this->minimumRoomSize );

        int dungeonTop = ( this->height - this->minimumRoomSize <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( this->width - this->minimumRoomSize <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), this->minimumRoomSize );
        int dungeonWidth = max( dungeonWidthRnd(rng), this->minimumRoomSize );

        room = new Dungeon::Room( roomID, top + dungeonTop, left+dungeonLeft, dungeonHeight, dungeonWidth );
        roomID++;
    }
}

void DungeonGenerator::render(sf::RenderTarget& target)
{
    for ( int i = 0; i < vectorRooms.size(); i++ )
    {
        sf::RectangleShape roomRect;
        roomRect.setSize( sf::Vector2f( vectorRooms[i]->height, vectorRooms[i]->width) );
            //prompt.setPosition( (SCREEN_WIDTH - prompt.getLocalBounds().width) / 2 , 400);
        roomRect.setPosition(sf::Vector2f( ((vectorRooms[i]->width - vectorRooms[i]->top) / 2) , vectorRooms[i]->left )) ;
        //roomRect.setPosition( sf::Vector2f( vectorRooms[i]->top , vectorRooms[i]->left ) );
        roomRect.setFillColor( sf::Color::Black );
        roomRect.setOutlineThickness(5);
        roomRect.setOutlineColor( sf::Color::Red );
        target.draw(roomRect);
    }
}