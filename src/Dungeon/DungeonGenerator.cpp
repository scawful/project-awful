#include "DungeonGenerator.hpp"

void DungeonGenerator::initOriginRoom()
{
    rootRoom = new Dungeon::Room( this->roomID, 10, 10, 512, 512 );
    roomID++;
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator()
{
    this->allocatedRooms = alloc_size;
    this->usedRooms = 0;
    this->roomID = 0;
    this->dungeonID = 0;
    this->dungeonCount = 0;

    this->initOriginRoom();
    vectorRooms.push_back( rootRoom );

    for ( int i = 0; i < 20; i++ )
    {
        random_device rd; 
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
        uniform_int_distribution<int> splitRand(0, vectorRooms.size() - 1 ); // guaranteed unbiased
        auto splitID = splitRand(rng);

        Dungeon::Room *roomToSplit = vectorRooms[splitID];
        if ( roomToSplit->splitRoom() )
        {
            vectorRooms.push_back( roomToSplit->getLeftChild() );
            vectorRooms.push_back( roomToSplit->getRightChild() );
        }
    }

    rootRoom->generateDungeon();

    for ( int i = 0; i < vectorRooms.size(); i++ )
    {
        if ( vectorRooms[i]->getDungeon() == NULL )
        {
            continue;
        }

        Dungeon::Room *dungeon = vectorRooms[i]->getDungeon();
        dungeonCount++;
    }
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

void DungeonGenerator::render(sf::RenderTarget& target)
{
    sf::RectangleShape rootRect;
    rootRect.setSize( sf::Vector2f( rootRoom->height, rootRoom->width ) );
    rootRect.setPosition(sf::Vector2f( rootRoom->left, rootRoom->top ) );
    rootRect.setFillColor( sf::Color::White );
    rootRect.setOutlineThickness(5);
    rootRect.setOutlineColor( sf::Color::Blue );
    target.draw(rootRect);


    for ( int i = 0; i < vectorRooms.size(); i++ )
    {
        sf::RectangleShape roomRect;
        roomRect.setPosition( sf::Vector2f( vectorRooms[i]->top, vectorRooms[i]->left ) ) ;
        roomRect.setSize( sf::Vector2f( vectorRooms[i]->height, vectorRooms[i]->width ) );
        //roomRect.setPosition( sf::Vector2f( vectorRooms[i]->top , vectorRooms[i]->left ) );
        roomRect.setFillColor( sf::Color::Green );
        roomRect.setOutlineThickness(5);
        roomRect.setOutlineColor( sf::Color::Blue );
        target.draw(roomRect);
    }

    rootRoom->drawRoom(target);



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