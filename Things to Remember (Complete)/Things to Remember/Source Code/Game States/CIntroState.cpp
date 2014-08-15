#include "CIntroState.h"
#include "CStartMenuState.h"
#include "Globals.h"

CIntroState *CIntroState::inst = 0;

void CIntroState::Init()
{
	Debug *dbg = Debug::GetInstance();
	
	musicStarted = false;

	text = NULL;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	bg = load_image("Rose.png");

	text = TTF_RenderText_Solid(font,"Things to Remember",textColor);

	myButton = new Button(0,0," Begin ", 36);
	myButton->SetX((SCREEN_W - myButton->GetCollisionBox().w)/2 + 4);
	myButton->SetY((SCREEN_H - myButton->GetCollisionBox().h)/2 - 14);

	dbg->Print("Intro Init \n");
}

void CIntroState::Finalize()
{
	Debug *dbg = Debug::GetInstance();

	SDL_FreeSurface(bg);
	SDL_FreeSurface(text);
	delete myButton;
	dbg->Print("Intro Finalize \n");
}

void CIntroState::Draw(CGame *game)
{
	SDL_FillRect(mainScreen,&mainScreen->clip_rect,SDL_MapRGB(mainScreen->format,0x00,0x00,0x00)); //fill screen with black
	DrawSurface(-20,20,bg,mainScreen);
	DrawSurface((SCREEN_W - text->w)/2,(SCREEN_H - text->h)/14,text,mainScreen);
	myButton->Draw();
}

void CIntroState::Update(CGame *game)
{
	myButton->Update();

	if(musicStarted == false)
	{
		Mix_FadeInChannel(1, game->music, -1, MUSIC_FADE_IN);
		musicStarted = true;
	}
}

void CIntroState::HandleEvents(CGame *game)
{
	if(SDL_PollEvent(&event))
	{
		myButton->HandleEvents(event);

		if(myButton->wasLeftClicked())
		{
			game->ChangeState(CStartMenuState::GetInstance());
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
void CIntroState::Pause()
{
	Debug *dbg = Debug::GetInstance();
	dbg->Print("Intro Paused \n");
}
void CIntroState::Resume()
{
	Debug *dbg = Debug::GetInstance();
	dbg->Print("Intro Resumed \n");
}

