#include "Globals.h"

ParticleSys::ParticleSys(int type, int w, int h)
{
	effect = type;

	levelW = w;
	levelH = h;

	maxSpeed = 0;

	hidden = false;

	InitEffect(type, levelW, levelH);
}

ParticleSys::~ParticleSys()
{
	if(effect != NONE)
	{
		for(int i = 0; i < TOTAL_PARTICLES; i++)
		{
			delete particles[i];
		}	
	}
}

void ParticleSys::Hide()
{
	for(int i = 0; i < TOTAL_PARTICLES; i++)
	{
		particles[i]->Kill();
	}
	
	if(!hidden)
	{
		hidden = true;
	}
}

void ParticleSys::Show()
{
	for(int i = 0; i < TOTAL_PARTICLES; i++)
	{
		particles[i]->Res();
	}

	if(hidden)
	{
		hidden = false;
	}
}

void ParticleSys::InitEffect(int effect, int levelW, int levelH)
{
		switch(effect)
		{
		case STARFIELD:
			maxSpeed = 10;

			srand((unsigned int)time(NULL));

			for(int i = 0; i < TOTAL_PARTICLES; i++)
			{
				particles[i] = new Particle(gameCamera.x + (rand() % gameCamera.w), (gameCamera.y + (rand() % gameCamera.h - PARTICLE_H)), PARTICLE_WHITE, rand() % 255);

				// Make the more transparent ( and therefore more distant ) stars move slower to appear farther away
				if(particles[i]->alpha > 175)
				{
					particles[i]->yVel = (rand() % 6) + 6; // 6 - 12 possible velocity for nearer stars
				}
				else if(particles[i]->alpha <= 175)
				{
					particles[i]->yVel = (rand() % 4) + 1;  // 1 - 4 possible velocity for distant stars
				}
			}
			break;

			case SNOW:

			srand((unsigned int)time(NULL));

			for(int i = 0; i < TOTAL_PARTICLES; i++)
			{
				particles[i] = new Particle(gameCamera.x + (rand() % gameCamera.w), (gameCamera.y + (rand() % gameCamera.h - PARTICLE_H)), PARTICLE_WHITE, rand() % 255);

				particles[i]->yVel = (rand() % 2) + 1; // 2 - 6 pixels per frame possible velocity

				particles[i]->SetTimer((rand() % 6) + 2); // drift delay

			}
			break;
		}
}

void ParticleSys::DoEffect(int effect, int levelW, int levelH)
{
	switch(effect)
	{
	case STARFIELD:
		srand((unsigned int)time(NULL));

		for(int i = 0; i < TOTAL_PARTICLES; i++)
		{			
			if(particles[i]->GetCollisionBox().y > (gameCamera.y + gameCamera.h))
			{
				particles[i]->SetY(-(rand() % (gameCamera.y + (gameCamera.h/6))) + 1);
			}
		}
		break;

	case SNOW:
		srand((unsigned int)time(NULL));

		for(int i = 0; i < TOTAL_PARTICLES; i++)
		{			
 			if((particles[i]->GetCollisionBox().x < 0) || (particles[i]->GetCollisionBox().y + PARTICLE_H > levelH) || (particles[i]->GetCollisionBox().x + PARTICLE_W > levelW))
			{
				particles[i]->SetY(-(rand() % (levelH/8)) + 1);
				particles[i]->SetX((rand() % (levelW)) + 1);
			}
			
			double max = 2*PI;
			double n = (rand() % ((int)max)) + 1;
			double a = cos(n);

			particles[i]->DecTimer();

			if(a > 0)
			{
				if(particles[i]->GetTimer() == 0)
				{
					particles[i]->xVel = (rand() % drift) + 1;
					particles[i]->SetTimer((rand() % 6) + 2); // drift delay
				}
			}
			else if(a <= 0)
			{
				if(particles[i]->GetTimer() == 0)
				{
					particles[i]->xVel = -1 * ((rand() % drift) + 1);
					particles[i]->SetTimer((rand() % 6) + 2); // drift delay
				}
			}

		}
		break;
	}
}

void ParticleSys::Update()
{
	if(effect != NONE)
	{
		for(int i = 0; i < TOTAL_PARTICLES; i++)
		{
			particles[i]->Update();
		}

		DoEffect(effect, levelW, levelH);
	}
}

void ParticleSys::ChangeEffect(int newEffect)
{
	effect = newEffect;
	ResetVariables();
	InitEffect(effect, levelW, levelH);
}

void ParticleSys::Draw(SDL_Surface *particleSheet, SDL_Rect *particleClips)
{
	if(effect != NONE)
	{
		for(int i = 0; i < TOTAL_PARTICLES; i++)
		{
			SDL_SetAlpha(particleSheet,SDL_SRCALPHA,particles[i]->alpha);
			particles[i]->Draw(particleSheet, particleClips);
		}
	}
}