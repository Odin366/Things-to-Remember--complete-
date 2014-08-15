#include "Globals.h"

Particle::Particle(int x, int y, int newType, int newAlpha)
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = PARTICLE_W;
	collisionBox.h = PARTICLE_H;

	type = newType;

	xVel = 0;
	yVel = 0;

	alpha = newAlpha;

	alive = true;
	
	timer = 0;
}

Particle::~Particle()
{
}

void Particle::Update()
{
	if(alive)
	{
		collisionBox.x += xVel;
		collisionBox.y += yVel;
	}
}

void Particle::Draw(SDL_Surface *spritesheet, SDL_Rect *clips)
{
	if(alive)
	{
		if(CollisionTest(collisionBox,gameCamera)) //if it's onscreen
		{
			DrawSurface(collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, spritesheet, mainScreen, &clips[type]);
		}
	}
}