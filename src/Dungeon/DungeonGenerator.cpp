#include "DungeonGenerator.hpp"

void DungeonGenerator::initOriginRoom()
{
    rootRoom = new Dungeon::Room( this->roomID, (SCREEN_HEIGHT - 512) / 2, (SCREEN_WIDTH - 512) / 2, 512, 512 );
    roomID++;
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator()
{
    this->allocatedRooms = alloc_size;
    this->usedRooms = 0;
    this->roomID = 0;
    this->dungeonID = 0;

    this->initOriginRoom();
    vectorRooms.push_back( rootRoom );

    for ( int i = 0; i < 5; i++ )
    {
        random_device rd; 
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
        maximum = room->height - room->getMinimumRoomSize();
    else
        maximum = room->width - room->getMinimumRoomSize();

    if ( maximum <= room->getMinimumRoomSize() )
        return false;

    // split 
    uniform_int_distribution<int> splitRand(0,maximum); // guaranteed unbiased
    auto split = splitRand(rng);

    if ( split < room->getMinimumRoomSize() )
    {
        split = room->getMinimumRoomSize();
    }

    if ( horizontal )
    {
        cout << "Left Child: " << roomID << " " << rootRoom->top << " " << rootRoom->left << " " << split << " " << room->width << endl;
        room->setLeftChild( new Dungeon::Room( roomID, rootRoom->top, rootRoom->left, split, room->width ) );
        roomID++;
        cout << "Right Child: " << roomID << " " << rootRoom->top + split << " " << rootRoom->left << " " << room->height - split << " " << room->width << endl;
        room->setRightChild( new Dungeon::Room( roomID, rootRoom->top + split, rootRoom->left, room->height - split, room->width ) );
        roomID++;
    }
    else
    {
        cout << "Left Child: " << roomID << " " << rootRoom->top << " " << rootRoom->left << " " << room->height << " " << split << endl;
        room->setLeftChild( new Dungeon::Room( roomID, rootRoom->top, rootRoom->left, room->height, split ) );
        roomID++;
        cout << "Right Child: " << roomID << " " << room->top << " " << rootRoom->left + split << " " << room->height << " " << room->width - split << endl;
        room->setRightChild( new Dungeon::Room( roomID, rootRoom->top, rootRoom->left + split, room->height, room->width - split ) );
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
        uniform_int_distribution<int> dungeonTopRnd(0, room->height - room->getMinimumRoomSize() );
        uniform_int_distribution<int> dungeonLeftRnd(0, room->width - room->getMinimumRoomSize() );

        int dungeonTop = ( room->height - room->getMinimumRoomSize() <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( room->width - room->getMinimumRoomSize() <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, room->height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, room->width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), room->getMinimumRoomSize() );
        int dungeonWidth = max( dungeonWidthRnd(rng), room->getMinimumRoomSize() );
        
        cout << "Dungeon: " << dungeonID << " " << rootRoom->top + dungeonTop << " " << rootRoom->left + dungeonLeft << " " << dungeonHeight << " " << dungeonWidth << endl;
        room->setDungeonRoom( new Dungeon::Room( dungeonID, rootRoom->top + dungeonTop, rootRoom->left + dungeonLeft, dungeonHeight, dungeonWidth ) );
        dungeonRooms.push_back( room );
        dungeonID++;
    }
}

void DungeonGenerator::render(sf::RenderTarget& target)
{
    sf::RectangleShape rootRect;
    rootRect.setSize( sf::Vector2f( rootRoom->height, rootRoom->width) );
    rootRect.setPosition(sf::Vector2f( rootRoom->left, rootRoom->top ) );
    rootRect.setFillColor( sf::Color::White );
    rootRect.setOutlineThickness(5);
    rootRect.setOutlineColor( sf::Color::Blue );
    target.draw(rootRect);

    for ( int i = 0; i < vectorRooms.size(); i++ )
    {
        sf::RectangleShape roomRect;
        roomRect.setSize( sf::Vector2f( vectorRooms[i]->height, vectorRooms[i]->width ) );
        roomRect.setPosition( sf::Vector2f( vectorRooms[i]->top, vectorRooms[i]->left ) ) ;
        //roomRect.setPosition( sf::Vector2f( vectorRooms[i]->top , vectorRooms[i]->left ) );
        roomRect.setFillColor( sf::Color::Black );
        roomRect.setOutlineThickness(5);
        roomRect.setOutlineColor( sf::Color::Red );
        target.draw(roomRect);
    }


    // for ( int i = 0; i < dungeonID; i++ )
    // {
    //     sf::RectangleShape dungeonRect;
    //     dungeonRect.setSize( sf::Vector2f( dungeonRooms[i]->height, dungeonRooms[i]->width) );
    //     dungeonRect.setPosition(sf::Vector2f( dungeonRooms[i]->top , dungeonRooms[i]->left )) ;
    //     dungeonRect.setFillColor( sf::Color::Black );
    //     dungeonRect.setOutlineThickness(5);
    //     dungeonRect.setOutlineColor( sf::Color::Red );
    //     target.draw(dungeonRect);
    // }

    // for( int i = 0; i < 512; i++ ) 
    // {
    //     for( int j = 0; j < 512; j++ )
            
    // }
}