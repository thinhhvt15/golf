#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#include "Common_Function.h"
#include "Math.h"
#include "RenderWindow.h"

class Tile
{
    public:
		Tile( int x, int y, int tileType );
		~Tile();

		void render( SDL_Rect& camera, RenderWindow& window, SDL_Texture* texture, SDL_Rect* gTileClips );

		int getType();

		SDL_Rect getBox();

    private:
		SDL_Rect mBox;
		int mType;
};


#endif // TILES_H_INCLUDED
