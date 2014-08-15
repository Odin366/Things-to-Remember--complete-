#ifndef _PlayerCLASS_H
#define _PlayerCLASS_H

#include "CObject.h"
#include "CTile.h"
#include "CLevel.h"

class Player: public Object
{
private:
	bool   showBox;
	bool   jumping;
	bool   falling;

	bool dead;

	int startX;
	int startY;

	int gravity;

public:
	
	Player(Level *level);
	~Player();

	bool CollisionVer(int x, int y, int &tileX, Level *level);
	bool CollisionHor(int x, int y, int &tileY, Level *level);
	
	void Handle_Events(SDL_Event event, Level *level);
	void Update(Level *level);
	void Draw(Level *level);
	void ToggleBox();

	Uint8 *keys;

	void CenterCamera(Level *level);

	bool isFalling()
	{
		return falling;
	}

	bool isJumping()
	{
		return jumping;
	}

	bool isDead()
	{
		return dead;
	}

	void Reset()
	{
		SetX(startX);
		SetY(startY - PLAYER_H/2);
	}

	void Kill()
	{
		dead = true;
	}

	void Rez()
	{
		dead = false;
	}


};

#endif