#include "CMenuState.h"
#include "Globals.h"

CMenuState *CMenuState::inst = 0;

void CMenuState::Init()
{
	Debug *dbg = Debug::GetInstance();

	text = NULL;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	text = TTF_RenderText_Solid(font,"MenuState",textColor);
	dbg->Print("Menu Init \n");
}

void CMenuState::Finalize()
{
	Debug *dbg = Debug::GetInstance();

	SDL_FreeSurface(text);
	dbg->Print("Menu Finalize \n");
}

void CMenuState::Draw(CGame *game)
{
	Debug *dbg = Debug::GetInstance();

	SDL_FillRect(mainScreen,&mainScreen->clip_rect,SDL_MapRGB(mainScreen->format,0,0,0));
	DrawSurface((SCREEN_W - text->w)/2, (SCREEN_H - text->h)/2,text,mainScreen);
}

void CMenuState::Update(CGame *game)
{
}

void CMenuState::HandleEvents(CGame *game)
{
	if(SDL_PollEvent(&event))
	{
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

			case SDLK_m:
				game->PopState();
				break;

			case SDLK_ESCAPE:
				game->StopRunning();
				break;
			}
		}
	}
}
void CMenuState::Pause()
{
	Debug *dbg = Debug::GetInstance();

	dbg->Print("Menu Paused \n");
}
void CMenuState::Resume()
{
	Debug *dbg = Debug::GetInstance();

	dbg->Print("Menu Resumed \n");
}