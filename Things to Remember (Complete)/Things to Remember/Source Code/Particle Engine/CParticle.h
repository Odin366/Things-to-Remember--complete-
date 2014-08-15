#include "SDL.h"

class Particle
{
public:
	Particle(int x, int y, int newType, int newAlpha);
	~Particle();

	void Update();
	void Draw(SDL_Surface *spritesheet, SDL_Rect *clips);

	int GetType()
	{
		return type;
	}

	void SetX(int x)
	{
		collisionBox.x = x;
	}

	void SetY(int y)
	{
		collisionBox.y = y;
	}

	int xVel;
	int yVel;
	
	SDL_Rect GetCollisionBox()
	{
		return collisionBox;
	}

	bool isAlive()
	{
		return alive;
	}

	void Kill()
	{
		if(alive == true)
		{
			alive = false;
		}
	}

	void Res() // ressurect 
	{
		if(alive == false)
		{
			alive = true;
		}
	}

	int GetTimer()
	{
		return timer;
	}

	void DecTimer()
	{
		timer--;
	}

	void incTimer()
	{
		timer++;
	}

	void SetTimer(int a)
	{
		timer = a;
	}

	int alpha;

private:

	int type;

	bool alive;

	SDL_Rect collisionBox;

	int timer;
};