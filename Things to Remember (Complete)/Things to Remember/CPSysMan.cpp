#include "CPSysMan.h"

PSysMan *PSysMan::inst = 0;

PSysMan::PSysMan()
{
	particleSheet = load_image("particles.png");
	CreateParticleClips(particleClips);

	levelW = 0;
	levelH = 0;
}

PSysMan::~PSysMan()
{
	if(!systems.empty())
	{
		for(int i = 0; i < (int) systems.size(); i++)
		{
			systems.pop_back();
		}
	}

	SDL_FreeSurface(particleSheet);
}

void PSysMan::PushSys(int type)
{
	ParticleSys *pSys = new ParticleSys(type, levelW, levelH);
	systems.push_back(pSys);
}

void PSysMan::PopSys()
{
	delete systems.back();
	systems.pop_back();
}

void PSysMan::HideSys(int sys)
{
	for(int i = 0; i < (int)systems.size(); i++)
	{
		if(systems[i]->GetType() == sys)
		{
			systems[i]->Hide();
			break;
		}
	}
}

void PSysMan::ShowSys(int sys)
{
	for(int i = 0; i < (int)systems.size(); i++)
	{
		if(systems[i]->GetType() == sys)
		{
			systems[i]->Show();
			break;
		}
	}
}

void PSysMan::KillEffects() // change to set effects to dead
{
	if(!systems.empty())
	{
		for(int i = 0; i < (int) systems.size(); i++)
		{
			systems[i]->Hide();
		}
	}
}

void PSysMan::ResEffects() // change to set effects to dead
{
	if(!systems.empty())
	{
		for(int i = 0; i < (int) systems.size(); i++)
		{
			systems[i]->Show();
		}
	}
}

void PSysMan::Update()
{
	if(!systems.empty())
	{
		for(int i = 0; i < (int) systems.size(); i++)
		{
			if(systems[i]->GetW() != levelW)
			{
				systems[i]->SetW(levelW);
			}

			if(systems[i]->GetH() != levelH)
			{
				systems[i]->SetH(levelH);
			}

			systems[i]->Update();
		}
	}
}

void PSysMan::Draw()
{
	if(!systems.empty())
	{
		for(int i = 0; i < (int) systems.size(); i++)
		{
			systems[i]->Draw(particleSheet, particleClips);
		}
	}
}
