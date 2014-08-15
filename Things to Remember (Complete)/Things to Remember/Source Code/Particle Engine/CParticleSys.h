#ifndef _CPARTICLESYS_H
#define _CPARTICLESYS_H

const int TOTAL_PARTICLES  = 100;
const int PARTICLE_SPRITES = 9;

const int PARTICLE_W = 3;
const int PARTICLE_H = 3;

// SNOW
const int drift = 4;

#include "SDL.h"
#include "CParticle.h"

class ParticleSys
{
public:

	void Update();
	void Draw(SDL_Surface *particleSheet, SDL_Rect *particleClips);

	void ChangeEffect(int newEffect);

	void Hide();
	void Show();
	
	void InitEffect(int effect, int levelW, int levelH);
	void DoEffect(int effect, int levelW, int levelH);
	
	void ResetVariables()
	{
		maxSpeed = 0;
	}

	int GetType()
	{
		return effect;
	}

	bool isHidden()
	{
		return hidden;
	}

	int maxSpeed; // particle speed

	ParticleSys(int type, int w, int h);
	~ParticleSys();


	int GetW()
	{
		return levelW;
	}

	int GetH()
	{
		return levelH;
	}

	void SetW(int a)
	{
		levelW = a;
	}

	void SetH(int a)
	{
		levelH = a;
	}

private:
	
	Particle *particles[TOTAL_PARTICLES];

	int levelW;
	int levelH;

	int effect;

	bool hidden;

};

#endif