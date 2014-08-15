#include "CInGameState.h"
#include "Globals.h"
#include "CIntroState.h"

CInGameState *CInGameState::inst = 0;

void CInGameState::Init()
{
	Debug *dbg = Debug::GetInstance();

	text = NULL;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	

	CreateTileClips(tileClips);
	tileSheet = load_image("tiles.png");
	
	myPSysMan = PSysMan::GetInstance();

	if(tileSheet == NULL)
	{
		dbg->Print("Images failed to initialize");
	}

	levelMan = new LevelMan("Map1.txt");
	player = new Player(levelMan->GetLevel());	

	myPSysMan->SetW(levelMan->GetLevel()->GetWidth());
	myPSysMan->SetH(levelMan->GetLevel()->GetHeight());

	
	myPSysMan->PushSys(SNOW);

	dbg->Print("InGame Init \n");

}

void CInGameState::Finalize()
{
	Debug *dbg = Debug::GetInstance();

	delete player;
	delete levelMan;
	myPSysMan->DestroyInstance();

	SDL_FreeSurface(tileSheet);
	SDL_FreeSurface(text);
	dbg->Print("InGame Finalize \n");
}

void CInGameState::Draw(CGame *game)
{
	levelMan->Draw(tileClips,tileSheet, player, myPSysMan);
}

void CInGameState::Update(CGame *game)
{
	levelMan->Update(player, myPSysMan);

	if((levelMan->GetLevel()->HasFadedOut()) && (levelMan->GetLevel()->GetID() == 7))
	{
		game->ChangeState(CIntroState::GetInstance());
	}
}

void CInGameState::HandleEvents(CGame *game)
{
	if(SDL_PollEvent(&event))
	{
		levelMan->Handle_Events(event);

		if(levelMan->GetLevel()->HasFadedIn() == true)
		{
			player->Handle_Events(event, levelMan->GetLevel());
		}

		if(levelMan->GetLevel()->GetID() == 7)
		{
			if((levelMan->GetLevel()->GetButton()->wasLeftClicked()) && (levelMan->GetLevel()->FadeOutBegun() == false))
			{
				Mix_FadeOutChannel(1, MUSIC_FADE_OUT);
				levelMan->GetLevel()->Finish();
			}
		}

		if(event.type == SDL_QUIT)
		{
			game->StopRunning();
		}
		else if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
			case SDLK_F11:
				game->ToggleFullScreen();
				break;

			case SDLK_ESCAPE:
				game->StopRunning();
				break;
			}
		}
	}
}
void CInGameState::Pause()
{
	Debug *dbg = Debug::GetInstance();
	dbg->Print("InGame Paused \n");
}
void CInGameState::Resume()
{
	Debug *dbg = Debug::GetInstance();
	dbg->Print("InGame Resumed \n");
}