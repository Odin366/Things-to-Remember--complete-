#ifndef COBJECT_H
#define COBJECT_H

#include "Globals.h"

class Object
{

protected:
	
	//static int NUMBER_OF_OBJECTS;

	SDL_Rect collisionBox;
	
	int xVel;
	int yVel;

	int type;

	int dir;

	int frame;


public:

	SDL_Rect GetCollisionBox()
	{
		return collisionBox;
	}

	void SetX(int amount)
	{
		collisionBox.x = amount;
	}

	void SetY(int amount)
	{
		collisionBox.y = amount;
	}

	void SetYvel(int amount)
	{
		yVel = amount;
	}

	void SetXvel(int amount)
	{
		xVel = amount;
	}

	int GetYvel()
	{
		return yVel;
	}

	int GetXvel()
	{
		return xVel;
	}



	//static int GetNumberofObjects();
		
};

//int CObject::NUMBER_OF_OBJECTS = 0;

#endif