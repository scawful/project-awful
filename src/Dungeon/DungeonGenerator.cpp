#include "DungeonGenerator.hpp"

void DungeonGenerator::initRootRoom( int x, int y, int width, int height)
{
    //rootRoom = new Dungeon::Room( roomID, (SCREEN_WIDTH - 600) / 2, (SCREEN_HEIGHT - 600) / 2, 600, 600 );
    //rootRoom = new Dungeon::Room( roomID, x, y, width, height );
    root = new Subdungeon( roomID, x, y, width, height );
    roomID++;
    cout << "Origin Room initialized\n";
}

DungeonGenerator::DungeonGenerator( int difficulty, int minimum, int x, int y, int width, int height )
{
    this->roomID = 0;
    this->dungeonID = 0;
    this->minimumRoomSize = minimum;
    this->difficultyLevel = difficulty;

    // random-number engine used (Mersenne-Twister in this case)
    // using the std::chrono clock as the random seed engine, since mingw uses a fixed seed for std::random
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    // create the source room that the dungeon is based on and put it in the vector of rooms
    this->initRootRoom( x, y, width, height );
    subdungeon_vector.push_back( root );

    // creates 42 children, so 22 dungeons
    while ( subdungeon_vector.size() < 42 )
    {
        uniform_int_distribution<int> splitRand(0, subdungeon_vector.size() - 1); // guaranteed unbiased
        auto splitID = splitRand(rng);

        Subdungeon *roomToSplit = subdungeon_vector[splitID];
        if ( this->splitRoom( roomToSplit ) )
        {
            subdungeon_vector.push_back( roomToSplit->getLeftChild() );
            subdungeon_vector.push_back( roomToSplit->getRightChild() );
        }
    }

    this->generateDungeon( root );
    this->generateCorridors( root );
}

DungeonGenerator::~DungeonGenerator()
{
    deleteDungeon( root );
    for ( int i = 0; i < corridors.size(); i++ )
    {
        Dungeon::Room *roomToFree = corridors[i];
        delete roomToFree;
        corridors[i] = NULL;
    }
    corridors.clear();
    
    cout << "DungeonGenerator destroyed\n";
}

void DungeonGenerator::deleteDungeon( Subdungeon *sub )
{
    if ( sub == NULL ) 
        return;
    
    this->deleteDungeon( sub->getLeftChild() );
    this->deleteDungeon( sub->getRightChild() );

    delete sub;
}

//bool DungeonGenerator::splitRoom( Dungeon::Room *room )
bool DungeonGenerator::splitRoom( Subdungeon *sub )
{
    float size_ratio = 0.3;

    if ( sub->getLeftChild() != NULL )
        return false;

    // horizontal
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
    uniform_int_distribution<int> horizRand(0,1); // guaranteed unbiased
    auto horizontal = horizRand(rng);

    int maximum = 0;
    if ( horizontal )
        maximum = sub->height;
    else
        maximum = sub->width;

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
        sub->setLeftChild( new Subdungeon( roomID, sub->top, sub->left, sub->width, split  ) );
        roomID++;

        cout << "Right Child: ";
        sub->setRightChild( new Subdungeon( roomID, sub->top + split, sub->left, sub->width , sub->height - split ) );
        roomID++;
    }
    else
    {
        cout << "Left Child: ";
        sub->setLeftChild( new Subdungeon( roomID, sub->top, sub->left, split, sub->height ) );
        roomID++;
        
        cout << "Right Child: ";
        sub->setRightChild( new Subdungeon( roomID, sub->top, sub->left + split, sub->width - split, sub->height ) );
        roomID++;
    }

    // calculate size ratio of the rooms to be created
    float leftChildRatio = (float)sub->getLeftChild()->width / (float)sub->getLeftChild()->height;
    float rightChildRatio = (float)sub->getRightChild()->width / (float)sub->getRightChild()->height;

    // if room does not match ratio, cleanup the old rooms and recall the function
    if ( leftChildRatio < size_ratio || rightChildRatio < size_ratio )
    {
        roomID -= 2;
        Subdungeon *cleanup = sub->getLeftChild();
        Subdungeon *cleanup2 = sub->getRightChild();
        delete cleanup;
        delete cleanup2;
        sub->setLeftChild( NULL );
        sub->setRightChild( NULL );
        splitRoom( sub );
    }
    
    return true;
}

bool DungeonGenerator::random_split( Subdungeon *sub )
{
    Subdungeon *newLeftChild, *newRightChild;
    float size_ratio = 0.45;

    // horizontal
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
    uniform_int_distribution<int> rand(0, 1); 
    auto random = rand(rng);

    if ( random == 1 )
    {
        // horizontal
        uniform_int_distribution<int> width(0, sub->width - this->minimumRoomSize); 
        auto randWidth = width(rng);

        cout << "Left Child: ";
        newLeftChild = new Subdungeon( roomID, sub->top, sub->left, randWidth, sub->height );
        roomID++;

        cout << "Right Child: ";
        newRightChild = new Subdungeon( roomID, sub->top + randWidth, sub->left, sub->width - randWidth , sub->height );
        roomID++;

        float leftChildRatio = (float)newLeftChild->width / (float)newLeftChild->height;
        float rightChildRatio = (float)newRightChild->width / (float)newRightChild->height;
        if ( leftChildRatio < size_ratio || rightChildRatio < size_ratio )
        {
            roomID -= 2;
            delete newLeftChild;
            delete newRightChild;
            cout << "children aborted by ratio " << endl;
            random_split( sub );
        }
    }
    else
    {
        // vertical
        uniform_int_distribution<int> height(0, sub->height - this->minimumRoomSize); 
        auto randHeight = height(rng);
        newLeftChild = new Subdungeon( roomID, sub->top, sub->left, sub->width, randHeight );
        newRightChild = new Subdungeon( roomID, sub->top, sub->left + randHeight, sub->width, sub->height - randHeight );

        float leftChildRatio = newLeftChild->height / newLeftChild->width;
        float rightChildRatio = newRightChild->height / newRightChild->width;
        if ( leftChildRatio < size_ratio || rightChildRatio < size_ratio )
        {
            roomID -= 2;
            delete newLeftChild;
            delete newRightChild;
            cout << "children aborted by ratio " << endl;
            random_split( sub );
        }
    }

    sub->setLeftChild( newLeftChild );
    sub->setRightChild( newRightChild );
    newLeftChild->setSibling(newRightChild);
    newRightChild->setSibling(newLeftChild);
    return true;
}

void DungeonGenerator::generateDungeon( Subdungeon *sub )
{
    if ( sub->getLeftChild() != NULL ) 
    { 
        // recursively generate 
        this->generateDungeon( sub->getLeftChild() );
        this->generateDungeon( sub->getRightChild() );
    } 
    else 
    { 
        // random-number engine used (Mersenne-Twister in this case)
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

        // if leaf node, create a dungeon within the minimum size constraints
        uniform_int_distribution<int> dungeonTopRnd(0, sub->height - this->minimumRoomSize );
        uniform_int_distribution<int> dungeonLeftRnd(0, sub->width - this->minimumRoomSize );

        int dungeonTop = ( sub->height - this->minimumRoomSize <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( sub->width - this->minimumRoomSize <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, sub->height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, sub->width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), this->minimumRoomSize );
        int dungeonWidth = max( dungeonWidthRnd(rng), this->minimumRoomSize );

        cout << "Dungeon: ";
        sub->addRoom( new Room( roomID, sub->top + dungeonTop, sub->left + dungeonLeft, dungeonWidth, dungeonHeight ) );
        roomID++;
    }
}

void DungeonGenerator::generateCorridors( Subdungeon *sub )
{
    if ( sub->isLeaf() )
    {
        this->generateCorridorBetween( sub, sub->getSibling() );
        return;
    }

    this->generateCorridors( sub->getLeftChild() );
    this->generateCorridors( sub->getRightChild() );

}

void DungeonGenerator::generateCorridorBetween( Subdungeon *left, Subdungeon *right )
{
    int corridorDepth = 10;
    Room *leftRoom = left->getRoom();
    Room *rightRoom = right->getRoom();

    // get a random point on each room to connect
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

    int lx = leftRoom->top + corridorDepth;
    int lw = leftRoom->top + leftRoom->width - corridorDepth;
    uniform_int_distribution<int> leftPointX( lx, lw );
    float leftPointXRand = leftPointX(rng);

    int ly = leftRoom->left + corridorDepth;
    int lh = leftRoom->left + leftRoom->height - corridorDepth;
    uniform_int_distribution<int> leftPointY( ly, lh );
    float leftPointYRand = leftPointY(rng);

    int rx = rightRoom->top + corridorDepth;
    int rw = rightRoom->top + rightRoom->width - corridorDepth;
    uniform_int_distribution<int> rightPointX( rx, rw );
    float rightPointXRand = rightPointX(rng);

    int ry = rightRoom->left + corridorDepth;
    int rh = rightRoom->left + rightRoom->height - corridorDepth;
    uniform_int_distribution<int> rightPointY( ry, rh );
    float rightPointYRand = rightPointY(rng);

    sf::Vector2f leftPoint( leftPointXRand, leftPointYRand );
    sf::Vector2f rightPoint( rightPointXRand, rightPointYRand );
    
    // tinfoil hat
    // ensuring that the left room is actually on the left 
    if ( leftPoint.x > rightPoint.x )
    {
        sf::Vector2f temp = leftPoint;
        leftPoint = rightPoint;
        rightPoint = temp;
    }

    int corridorWidth = leftPoint.x - rightPoint.x;
    int corridorHeight = leftPoint.y - rightPoint.y;

    cout << "leftPoint: (" << leftPoint.x << ", " << leftPoint.y << "), rightPoint: (" << rightPoint.x << ", " << rightPoint.y << "), width: " << corridorWidth << ", height: " << corridorHeight << endl;

    // two points are not aligned horizontally
    if ( corridorWidth < 0 )
    {
        // random
        uniform_int_distribution<int> boolean(0,1); // guaranteed unbiased
        auto horizontal = boolean(rng);
        if ( horizontal )
        {
            // add corridor to the right
            corridors.push_back( new Dungeon::Room( -1, leftPoint.x, leftPoint.y, abs(corridorWidth) + corridorDepth, corridorDepth));

            if ( corridorHeight < 0 )
                corridors.push_back( new Dungeon::Room( -1, rightPoint.x, leftPoint.y, corridorDepth, abs(corridorHeight)));
            else
                corridors.push_back( new Dungeon::Room( -1, rightPoint.x, leftPoint.y, corridorDepth, -(abs(corridorHeight))));
        }
        else
        {
            if ( corridorHeight < 0 )
                corridors.push_back( new Dungeon::Room( -1, leftPoint.x, leftPoint.y, corridorDepth, abs(corridorHeight) ));
            else
                corridors.push_back( new Dungeon::Room( -1, leftPoint.x, rightPoint.y, corridorDepth, abs(corridorHeight) ));

            corridors.push_back( new Dungeon::Room( -1, leftPoint.x, rightPoint.y, abs(corridorWidth) + corridorDepth, corridorDepth));
        }
    }
    else
    {
        if ( corridorHeight < 0 )
            corridors.push_back( new Dungeon::Room( -1, leftPoint.x, leftPoint.y, corridorDepth, abs(corridorHeight)));
        else
            corridors.push_back( new Dungeon::Room( -1, rightPoint.x, rightPoint.y, corridorDepth, abs(corridorHeight)));
    }
}

void DungeonGenerator::render(sf::RenderTarget& target)
{
    sf::RectangleShape rootRect;
    rootRect.setSize( sf::Vector2f( rootRoom->height, rootRoom->width ) );
    rootRect.setPosition( sf::Vector2f( rootRoom->top, rootRoom->left ) );
    rootRect.setFillColor( sf::Color::White );
    // rootRect.setOutlineThickness(5);
    // rootRect.setOutlineColor( sf::Color::Blue );
    target.draw(rootRect);

    rootRoom->drawRoom(target);

    for ( int i = 0; i < corridors.size(); i++ )
    {
        sf::RectangleShape corridorRect;
        corridorRect.setSize( sf::Vector2f( corridors[i]->height, corridors[i]->width ) );
        corridorRect.setPosition( sf::Vector2f( corridors[i]->top, corridors[i]->left) ) ; 
        corridorRect.setFillColor( sf::Color::Black );
        target.draw(corridorRect);
    }

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