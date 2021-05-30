#include "DungeonGenerator.hpp"

void DungeonGenerator::initOriginRoom()
{
    roomID = 0;
    rootRoom = new Dungeon::Room( roomID, 
                                  (SCREEN_WIDTH - 500) / 2, 
                                  (SCREEN_HEIGHT - 500) / 2, 
                                  500, 500 );
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator()
{
    this->usedRooms = 0;
    this->roomID = 0;
    this->dungeonID = 0;

    this->initOriginRoom();
    vectorRooms.push_back( rootRoom );

    while ( vectorRooms.size() < 15 )
    {
        random_device rd; 
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
        int splitID = 0;
        if ( vectorRooms.size() > 0 )
        {
            uniform_int_distribution<int> splitRand(0, vectorRooms.size() - 1); // guaranteed unbiased
            splitID = splitRand(rng);
        }   

        Dungeon::Room *roomToSplit = vectorRooms[splitID];
        if ( roomToSplit->splitRoom() )
        {
            vectorRooms.push_back( roomToSplit->getLeftChild() );
            vectorRooms.push_back( roomToSplit->getRightChild() );
        }
    }

    rootRoom->generateDungeon();
}

DungeonGenerator::~DungeonGenerator()
{
    deleteDungeon( rootRoom );
    cout << "DungeonGenerator destroyed\n";
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
    rootRect.setPosition( sf::Vector2f( rootRoom->top, rootRoom->left ) );
    rootRect.setFillColor( sf::Color::White );
    rootRect.setOutlineThickness(5);
    rootRect.setOutlineColor( sf::Color::Blue );
    target.draw(rootRect);

    rootRoom->drawRoom(target);

    // for ( int i = 0; i < vectorRooms.size(); i++ )
    // {
    //     if ( vectorRooms[i]->getDungeon() == NULL )
    //     {
    //         continue;
    //     }

    //     sf::RectangleShape roomRect;
    //     roomRect.setSize( sf::Vector2f( vectorRooms[i]->getDungeon()->height, vectorRooms[i]->getDungeon()->width ) );
    //     roomRect.setPosition( sf::Vector2f( vectorRooms[i]->getDungeon()->top, vectorRooms[i]->getDungeon()->left) ) ; 
    //     roomRect.setFillColor( sf::Color::Green );
    //     roomRect.setOutlineThickness(3);
    //     roomRect.setOutlineColor( sf::Color::Blue );
    //     target.draw(roomRect);

    //     // for ( int j = 0; j < vectorRooms[i]->getDungeon()->height; j++ )
    //     // {
    //     //     for ( int k = 0; k < vectorRooms[i]->getDungeon()->width; k++ )
    //     //     {

    //     //     }
    //     // }

    //     dungeonRooms.push_back( vectorRooms[i]->getDungeon() );
    // }

}