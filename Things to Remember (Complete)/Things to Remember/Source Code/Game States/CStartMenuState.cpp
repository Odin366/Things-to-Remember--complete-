#include "CStartMenuState.h"
#include "Globals.h"

CStartMenuState *CStartMenuState::inst = 0;

void CStartMenuState::Init()
{
	Debug *dbg = Debug::GetInstance();

	menuFont = TTF_OpenFont("dnealiancursive.ttf", 22);

	fader = load_image("fader.png");

	alpha = 255;
	
	button = new Button(0,0,"Continue",22);

	button->SetX((SCREEN_W - button->GetCollisionBox().w)/2);
	button->SetY((SCREEN_H - 2 * button->GetCollisionBox().h));

	fadedin = false;

	text = NULL;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	heart = load_image("heart.png");

	text  = TTF_RenderText_Solid(menuFont,"My love,",textColor);
	text2 = TTF_RenderText_Solid(menuFont,"You are the fire burning in my soul.",textColor);
	text3 = TTF_RenderText_Solid(menuFont,"You are my port in the storm and my solace in all pain.",textColor);
	text4 = TTF_RenderText_Solid(menuFont,"You are the sole image of perfection and the quintessence of loveliness.",textColor);
	text5 = TTF_RenderText_Solid(menuFont,"You are my passion, my inspiration, and my purpose.",textColor);
	text6 = TTF_RenderText_Solid(menuFont,"You are all the memories I will cherish most.",textColor);
	text7 = TTF_RenderText_Solid(menuFont,"And of course,",textColor);
	text8 = TTF_RenderText_Solid(menuFont,"You are the sunshine through the clouds on all of my rainy days.",textColor);
	text9 = TTF_RenderText_Solid(menuFont,"- The Perfectionist",textColor); 

	dbg->Print("StartMenu Init \n");
}

void CStartMenuState::Finalize()
{
	Debug *dbg = Debug::GetInstance();

	SDL_FreeSurface(fader);

	SDL_FreeSurface(heart);

	SDL_FreeSurface(text);
	SDL_FreeSurface(text2);
	SDL_FreeSurface(text3);
	SDL_FreeSurface(text4);
	SDL_FreeSurface(text5);
	SDL_FreeSurface(text6);
	SDL_FreeSurface(text7);
	SDL_FreeSurface(text8);
	SDL_FreeSurface(text9);

	delete button;

	TTF_CloseFont(menuFont);
	dbg->Print("StartMenu Finalize \n");
}

void CStartMenuState::Draw(CGame *game)
{
	SDL_FillRect(mainScreen,&mainScreen->clip_rect,SDL_MapRGB(mainScreen->format,0,0,0));

	DrawSurface((SCREEN_W - text->w)/2, 0,  text, mainScreen);
	DrawSurface(0, text->h + text2->h,  text2, mainScreen);
	DrawSurface(0, text->h + text2->h + text3->h,  text3, mainScreen);
	DrawSurface(0, text->h + text2->h + text3->h + text4->h,  text4, mainScreen);
	DrawSurface(0, text->h + text2->h + text3->h + text4->h + text5->h,  text5, mainScreen);
	DrawSurface(0, text->h + text2->h + text3->h + text4->h + text5->h + text6->h,  text6, mainScreen);
	DrawSurface(0, text->h + text2->h + text3->h + text4->h + text5->h + text6->h + text7->h,  text7, mainScreen);
	DrawSurface(0, text->h + text2->h + text3->h + text4->h + text5->h + text6->h + text7->h + text8->h,  text8, mainScreen);
	DrawSurface(0, SCREEN_H - heart->h - 50 - text->h/2 ,  text9, mainScreen);

	DrawSurface(SCREEN_W - heart->w*2, SCREEN_H - heart->h*3/2 - 50, heart, mainScreen);

	button->Draw();

	if(!fadedin)
	{
		if(alpha > 0)
		{
			DrawAlphaSurface(0, 0, fader, mainScreen, alpha);

			alpha -= FADE_SPEED;

			if(alpha <= 0)
			{
				alpha = 0;
				fadedin = true;
			}
		}
	}
}

void CStartMenuState::Update(CGame *game)
{
	button->Update();
}

void CStartMenuState::HandleEvents(CGame *game)
{
	if(SDL_PollEvent(&event))
	{
		button->HandleEvents(event);

		if(button->wasLeftClicked())
		{
			game->ChangeState(CInGameState::GetInstance());
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
void CStartMenuState::Pause()
{
	Debug *dbg = Debug::GetInstance();

	dbg->Print("StartMenu Paused \n");
}

void CStartMenuState::Resume()
{
	Debug *dbg = Debug::GetInstance();

	dbg->Print("StartMenu Resumed \n");
}