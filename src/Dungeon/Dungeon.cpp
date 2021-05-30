#include "Dungeon.hpp"

// Room

Dungeon::Room::Room(int id, int top, int left, int width, int height)
{
    this->id = id + 1;
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
        // if ( this->dungeon->top > 512 )
        //     this->dungeon->top -= 512;

        // if ( this->dungeon->left > 512 )
        //     this->dungeon->left -= 512;

        // if ( this->dungeon->width > 512 )
        //     this->width -= this->minimumRoomSize;

        // if ( this->dungeon->height > 512 )
        //     this->height -= this->minimumRoomSize;
        
        roomRect.setPosition( sf::Vector2f( this->dungeon->top, this->dungeon->left ) ) ;
        roomRect.setSize( sf::Vector2f( this->height, this->width ) );
        roomRect.setFillColor( sf::Color::Black );
        roomRect.setOutlineThickness(3);
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

    // int maximum = 0;
    // if ( horizontal )
    //     maximum = this->height - this->minimumRoomSize;
    // else
    //     maximum = this->width - this->minimumRoomSize;

    int split;
    if ( this->width / this->height >= 1.25 )
        split = 0;
    else if ( this->height / this->width >= 1.25 )
        split = 1;
    else
        split = horizRand(rng);

    if ( (min(this->height, this->width) / 2) < this->minimumRoomSize )
        return false;

    // split 
    uniform_int_distribution<int> splitRand(0, this->width - this->minimumRoomSize); // guaranteed unbiased
    split = splitRand(rng);

    if ( split < this->minimumRoomSize )
    {
        split = this->minimumRoomSize;
    }

    if ( horizontal )
    {
        cout << "Left Child: " << id << " : " << this->top << " " << this->left << " " << split << " " << this->width << endl;
        leftChild = new Dungeon::Room( id, this->top, this->left, split, this->width );

        cout << "Right Child: " << id << " : " << this->top + split << " " << this->left << " " << this->height - split << " " << this->width << endl;
        rightChild = new Dungeon::Room( id, this->top + split, this->left, this->height - split, this->width );
    }
    else
    {
        cout << "Left Child: " << id << " : " << this->top << " " << this->left << " " << this->height << " " << split << endl;
        leftChild = new Dungeon::Room( id, this->top, this->left, this->height, split );

        cout << "Right Child: " << id << " : " << this->top << " " << this->left + split << " " << this->height << " " << this->width - split << endl;
        rightChild = new Dungeon::Room( id, this->top, this->left + split, this->height, this->width - split );
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
        mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

        // if leaf node, create a dungeon within the minimum size constraints
        uniform_int_distribution<int> dungeonTopRnd(0, height - minimumRoomSize );
        uniform_int_distribution<int> dungeonLeftRnd(0, width - minimumRoomSize );

        int dungeonTop = ( height - minimumRoomSize <= 0 ) ? 0 : dungeonTopRnd(rng);
        int dungeonLeft =  ( width - minimumRoomSize <= 0 ) ? 0 : dungeonLeftRnd(rng);

        uniform_int_distribution<int> dungeonHeightRnd(0, height - dungeonTop );
        uniform_int_distribution<int> dungeonWidthRnd(0, width - dungeonLeft );

        int dungeonHeight = max( dungeonHeightRnd(rng), minimumRoomSize );
        int dungeonWidth = max( dungeonWidthRnd(rng), minimumRoomSize );
        
        cout << "Dungeon: " << this->top + dungeonTop << " " << this->left + dungeonLeft << " " << dungeonHeight << " " << dungeonWidth << endl;
        dungeon = new Dungeon::Room( 0, this->top + dungeonTop, this->left + dungeonLeft, dungeonHeight, dungeonWidth );
    }
}



// Door

Dungeon::Door::Door()
{
    
}

Dungeon::Door::~Door()
{
    
}