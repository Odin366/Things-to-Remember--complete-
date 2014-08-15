#ifndef _TILECLASS_H
#define _TILECLASS_H

#include "SDL.h"

class Tile
{

private:

	SDL_Rect collisionBox;
	bool isStartPos;
	bool showBox;

	bool solid;

	int ID;

public:

	Tile(int x, int y, int type);
	~Tile();

	void Display(SDL_Rect *TileClips, SDL_Surface *tileSheet);

	SDL_Rect GetCollisionBox()
	{
		return collisionBox;
	}

	int GetID()
	{
		return ID;
	}

	bool IsSolid()
	{
		return solid;
	}
	
	void SetID(int newID)
	{
		ID = newID;
	}

	bool IsStartPos()
	{
		return isStartPos;
	}

	void ToggleBox();

};

#endif 