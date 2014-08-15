#include "Globals.h"

Tile::Tile(int x, int y, int type)
{
	ID = type;
	isStartPos	= false;
	showBox		= false;
	solid		= true;
	

	switch(type)
	{
	case TILE_BLANK:
		solid = false;
		break;
	default:
		solid = true; // very, very true
		break;
	}

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = TILE_W;
	collisionBox.h = TILE_H;
}

Tile::~Tile()
{

}

void Tile::Display(SDL_Rect *TileClips, SDL_Surface *tileSheet)
{
	if(CollisionTest(gameCamera, collisionBox))
	{
		DrawSurface(collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y,tileSheet,mainScreen,&TileClips[ID]);

		if(solid)
		{
			showBox = true;
		}

		/*if(showBox == true)
		{
			rectangleRGBA(mainScreen,collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, (collisionBox.x + TILE_W) - gameCamera.x, (collisionBox.y + TILE_H) - gameCamera.y,255,0,0,255);
			lineRGBA(mainScreen,collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, (collisionBox.x + TILE_W) - gameCamera.x, (collisionBox.y + TILE_H) - gameCamera.y, 255, 0, 0, 255);
		}*/
	}
}


void Tile::ToggleBox()
{
	if(showBox == true)
	{
		showBox = false;
	}
	else if(showBox == false)
	{
		showBox = true;
	}
}
