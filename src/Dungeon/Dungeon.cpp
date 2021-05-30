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

    this->minimumRoomSize = 5;
}

Dungeon::Room::~Room()
{
    this->leftChild = NULL;
    this->rightChild = NULL;
}

void Dungeon::Room::drawRoom( sf::RenderTarget& target )
{
    if ( this->leftChild != NULL )
    {
        this->leftChild->drawRoom( target );
        this->rightChild->drawRoom( target );
    }
    else
    {
        sf::RectangleShape roomRect;
        roomRect.setPosition( sf::Vector2f( this->dungeon->top, this->dungeon->left ) ) ;
        roomRect.setSize( sf::Vector2f( this->dungeon->height, this->dungeon->width ) );
        roomRect.setFillColor( sf::Color::Black );
        roomRect.setOutlineThickness(5);
        roomRect.setOutlineColor( sf::Color::Red );
        target.draw(roomRect);
    }

}

bool Dungeon::Room::splitRoom()
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
        maximum = this->height - this->minimumRoomSize;
    else
        maximum = this->width - this->minimumRoomSize;

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
        cout << "Left Child: " <<  top << " " << left << " " << split << " " << width << endl;
        this->leftChild = new Dungeon::Room( roomID, top, left, split, width );

        cout << "Right Child: " << top + split << " " << left << " " << height - split << " " << width << endl;
        this->rightChild = new Dungeon::Room( roomID, top + split, left, height - split, width );
    }
    else
    {
        cout << "Left Child: " << top << " " << left << " " << height << " " << split << endl;
        this->leftChild = new Dungeon::Room( roomID, top, left, height, split );

        cout << "Right Child: " << top << " " << left + split << " " << height << " " << width - split << endl;
        this->rightChild = new Dungeon::Room( roomID, top, left + split, height, width - split );
    }
    
    return true;
}

void Dungeon::Room::generateDungeon()
{
    if( this->leftChild != NULL ) 
    { 
        // recursively generate 
        this->leftChild->generateDungeon();
        this->rightChild->generateDungeon();
    } 
    else 
    { 
        random_device rd;     // only used once to initialise (seed) engine
        mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)

        // if leaf node, create a dungeon within the minimum size constraints
        uniform_int_distribution<int> dungeonTopRnd(0, height - this->minimumRoomSize );
        uniform_int_distribution<int> dungeonLeftRnd(0, width - this->minimumRoomSize );

        int dungeonTop = ( height - this->minimumRoomSize <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( width - this->minimumRoomSize <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), this->minimumRoomSize );
        int dungeonWidth = max( dungeonWidthRnd(rng), this->minimumRoomSize );
        
        cout << "Dungeon: " << top + dungeonTop << " " << left + dungeonLeft << " " << dungeonHeight << " " << dungeonWidth << endl;
        dungeon = new Dungeon::Room( 0, top + dungeonTop, left + dungeonLeft, dungeonHeight, dungeonWidth );
    }
}



// Door

Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}