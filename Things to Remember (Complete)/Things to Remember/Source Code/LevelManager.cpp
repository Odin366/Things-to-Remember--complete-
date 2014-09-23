#include "LevelManager.h"

LevelMan::LevelMan(string initMap)
{
	curLevel = NULL;

	levelCount = 0;

	StartNextLevel();

	levelFinished = false;
}

LevelMan::~LevelMan()
{
	Finalize();
}

void LevelMan::StartNextLevel()
{
	if(curLevel != NULL)
	{
		curLevel->Finalize();
	}

	levelCount++;
	ostringstream convert;
	convert << "Map" << levelCount << ".txt";

	delete curLevel;

	curLevel = NULL;
	
	if(levelCount != 7)
	{
		curLevel = new Level(convert.str(),levelCount);
	}
	else if(levelCount == 7)
	{
		curLevel = new Level(convert.str(),"bgV.png",levelCount);
	}

	// Level Messages 
	switch(levelCount)
	{
	case 1:
		curLevel->SetMessage("Love can overcome any obstacle.");
		break;

	case 2:
		curLevel->SetMessage("Love is taking a risk.");
		break;

	case 3:
		curLevel->SetMessage("Love is a leap of faith.");
		break;

	case 4:
		curLevel->SetMessage("Love is doing the impossible.");
		break;

	case 5:
		curLevel->SetMessage("Love is persistent.");
		break;
	
	case 6:
		curLevel->SetMessage("Love finds a way.");
		break;

	case 7:
		curLevel->SetMessage("I love you.");
		break;
	}

	curLevel->SetID(levelCount);
}

void LevelMan::Update(Player *Player, PSysMan *PSysMan)
{
	if(levelFinished == true)
	{
		curLevel->Finish();
		levelFinished = false;
	}

	if(curLevel->isFinished())
	{
		if((curLevel->HasFadedOut()) && (curLevel->GetID() != 7))
		{
			StartNextLevel();

			PSysMan->SetW(curLevel->GetWidth());
			PSysMan->SetH(curLevel->GetHeight());

			Player->SetX(curLevel->GetStartX());
			Player->SetY(curLevel->GetStartY());

			Player->SetXvel(0);
			Player->SetYvel(0);
		}
	}
	else if(!curLevel->isFinished())
	{
		curLevel->Update();
		Player->Update(curLevel);
		PSysMan->Update();
	}
}

void LevelMan::Draw(SDL_Rect *TileClips,SDL_Surface *tileSheet, Player *player, PSysMan *myPSysMan)
{
	curLevel->Draw(TileClips,tileSheet);

	if(curLevel->MsgFadedIn() == true)
	{
		DrawSurface(curLevel->GetMsgX() - gameCamera.x, curLevel->GetMsgY() - gameCamera.y, curLevel->GetMsg(), mainScreen);

	}
	else if((curLevel->HasFadedIn() == true) && (curLevel->MsgFadedIn() == false))
	{
		if((curLevel->GetID() != 5) && (curLevel->GetID() != 6) && (curLevel->GetID() != 7))
		{
			curLevel->FadeMsgIn(MSG_FADE_SPEED, ((SCREEN_W - curLevel->GetMsg()->w)/2) - gameCamera.x, ((SCREEN_H - curLevel->GetMsg()->h)/4) - gameCamera.y);
		}
		else if((curLevel->GetID() == 5) || (curLevel->GetID() == 6))
		{
			curLevel->FadeMsgIn(MSG_FADE_SPEED, ((SCREEN_W - curLevel->GetMsg()->w)/2) - gameCamera.x, (6 * TILE_H) - gameCamera.y);
		}
		else if(curLevel->GetID() == 7)
		{
			curLevel->FadeMsgIn(MSG_FADE_SPEED, ((SCREEN_W - curLevel->GetMsg()->w)/2) - gameCamera.x, ((SCREEN_H - curLevel->GetMsg()->h)/10) - gameCamera.y);
		}
	}

	player->Draw(curLevel);
	myPSysMan->Draw();

	if(curLevel->HasFadedIn() == false)
	{
		curLevel->FadeIn(FADE_SPEED);
	}

	if(curLevel->isFinished())
	{
		if((curLevel->HasFadedOut() == false))
		{
			curLevel->FadeOut(FADE_SPEED);
		}
	}
}

void LevelMan::Handle_Events(SDL_Event event)
{
	curLevel->Handle_Events(event);
}

void LevelMan::Finalize()
{
	curLevel->Finalize();
	delete curLevel;
}
