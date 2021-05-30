#include "DungeonGenerator.hpp"

void DungeonGenerator::initOriginRoom()
{
    rootRoom = new Dungeon::Room( roomID, (SCREEN_WIDTH - 720) / 2, (SCREEN_HEIGHT - 720) / 2, 720, 720 );
    //rootRoom = new Dungeon::Room( roomID, 5, 5, SCREEN_WIDTH, SCREEN_HEIGHT );
    roomID++;
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator()
{
    this->roomID = 0;
    this->dungeonID = 0;
    this->minimumRoomSize = 100;

    // create the source room that the dungeon is based on and put it in the vector of rooms
    this->initOriginRoom();
    vectorRooms.push_back( rootRoom );

    while ( vectorRooms.size() < 42 )
    {
        random_device rd; 
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
        uniform_int_distribution<int> splitRand(0, vectorRooms.size() - 1); // guaranteed unbiased
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
        maximum = room->height;
    else
        maximum = room->width;

    maximum -= this->minimumRoomSize;

    if ( maximum <= this->minimumRoomSize )
        return false;

    // split 
    uniform_int_distribution<int> splitRand(0, maximum); // guaranteed unbiased
    auto split = splitRand(rng);

    if ( split < this->minimumRoomSize )
    {
        split = this->minimumRoomSize;
    }

    if ( horizontal )
    {
        cout << "Left Child: ";
        room->setLeftChild( new Dungeon::Room( roomID, room->top, room->left, room->width, split  ) );
        roomID++;

        cout << "Right Child: ";
        room->setRightChild( new Dungeon::Room( roomID, room->top + split, room->left, room->width , room->height - split ) );
        roomID++;
    }
    else
    {
        cout << "Left Child: ";
        room->setLeftChild( new Dungeon::Room( roomID, room->top, room->left, split, room->height ) );
        
        roomID++;
        cout << "Right Child: ";
        room->setRightChild( new Dungeon::Room( roomID, room->top, room->left + split, room->width - split, room->height ) );
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
        uniform_int_distribution<int> dungeonTopRnd(0, room->height - this->minimumRoomSize );
        uniform_int_distribution<int> dungeonLeftRnd(0, room->width - this->minimumRoomSize );

        int dungeonTop = ( room->height - this->minimumRoomSize <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( room->width - this->minimumRoomSize <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, room->height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, room->width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), this->minimumRoomSize );
        int dungeonWidth = max( dungeonWidthRnd(rng), this->minimumRoomSize );

        cout << "Dungeon: ";
        room->setDungeon( new Dungeon::Room( roomID, room->top + dungeonTop, room->left + dungeonLeft, dungeonWidth, dungeonHeight ) );
        roomID++;
    }
}

void DungeonGenerator::generateCorridorBetween( Dungeon::Room *leftRoom, Dungeon::Room *rightRoom )
{
    // get a random point on each room to connect
    random_device rd;    
    mt19937 rng(rd()); 

    uniform_int_distribution<int> leftPointX( leftRoom->top + 1, leftRoom->width - 1 );
    uniform_int_distribution<int> leftPointY( leftRoom->left + 1, leftRoom->height - 1 );

    sf::Vector2f leftPoint( leftPointX(rng), leftPointY(rng) );

    uniform_int_distribution<int> rightPointX( rightRoom->top + 1, rightRoom->width - 1 );
    uniform_int_distribution<int> rightPointY( rightRoom->left + 1, rightRoom->height - 1 );

    sf::Vector2f rightPoint( rightPointX(rng), rightPointY(rng) );

    // tinfoil hat
    // ensuring that the left room is actually on the left 
    if ( leftPoint.x > rightPoint.x )
    {
        sf::Vector2f temp = leftPoint;
        leftPoint = rightPoint;
        rightPoint = temp;
    }

    int corridorWidth = leftPoint.x - rightPoint.x;
    int corridorHeight = rightPoint.y - rightPoint.y;

    if ( corridorWidth != 0 )
    {
        uniform_int_distribution<int> boolean(0, 1);
        if ( boolean(rng) > 2 )
        {
            corridors.push_back( new Dungeon::Room(-1, leftPoint.x, leftPoint.y, abs(corridorWidth) + 10, 10));

            if ( corridorHeight < 0 )
            {
                corridors.push_back( new Dungeon::Room( -1, rightPoint.x, leftPoint.y, 10, abs(corridorHeight)));
            }
            else
            {
                corridors.push_back( new Dungeon::Room( -1, rightPoint.x, leftPoint.y, 10, -abs(corridorHeight)));
            }
        }
        else
        {
            if ( corridorHeight < 0 )
            {
                corridors.push_back( new Dungeon::Room( -1, leftPoint.x, leftPoint.y, 10, abs(corridorHeight) ));
            }
            else
            {
                corridors.push_back( new Dungeon::Room( -1, leftPoint.x, rightPoint.y, 10, abs(corridorHeight) ));
            }

            corridors.push_back( new Dungeon::Room( -1, leftPoint.x, rightPoint.y, abs(corridorWidth) + 10, 10));
        }
    }
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

    for ( int i = 0; i < vectorRooms.size(); i++ )
    {
        if ( vectorRooms[i]->getDungeon() == NULL )
        {
            continue;
        }

        sf::RectangleShape roomRect;
        roomRect.setSize( sf::Vector2f( vectorRooms[i]->getDungeon()->height, vectorRooms[i]->getDungeon()->width ) );
        roomRect.setPosition( sf::Vector2f( vectorRooms[i]->getDungeon()->top, vectorRooms[i]->getDungeon()->left) ) ; 
        roomRect.setFillColor( sf::Color( 120, 120, 120, 100 ) );
        roomRect.setOutlineThickness(2);
        roomRect.setOutlineColor( sf::Color::Green );
        target.draw(roomRect);
    }

}