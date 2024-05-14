#include "Tiles.h"


Tile::Tile( int x, int y, int tileType )
{
    mBox.x = x;
    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = tileType;
}
//Tile::~Tile()
//{
//    delete this;
//}

void Tile::render( SDL_Rect& camera, RenderWindow& window , SDL_Texture* texture, SDL_Rect* gTileClips)
{
    if( mathFunc::checkCollision( camera, mBox ) )
    {
        window.render( mBox.x - camera.x, mBox.y - camera.y, TILE_WIDTH, TILE_HEIGHT, texture, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}


