				/*||||||||||||||||||||||||||||||||||||
				|| SDL/C++ Game Engine				||
				|| "Alana's Valetine's Day Gift"    ||
				|| Created by Matt Berger			||
				||||||||||||||||||||||||||||||||||||*/
//______________________________________________________________________________//



#include "CGame.h"
#include "Globals.h"
#include <iostream>


int main( int argc, char *args[])
{

	CGame *game = CGame::GetInstance();
	Debug *dbg  = Debug::GetInstance();

	bool fullscreen = false;

	if(game->Initialize() == false)
	{
		dbg->Print("Failed to Initialize!");
		return 1;
	}

	if(game->LoadContent() == false)
	{
		dbg->Print("Failed to load content");
		return 1;
	}

	while(game->isRunning())
	{
		
		game->EventHandler();		
		game->Update(); 
		game->Draw();
		
		if(SDL_Flip(mainScreen) == -1)
		{
			dbg->Print("SDL_Flip failed");
			return 1;
		}

		SDL_Delay(1000/MAX_FPS);
			
	}

	game->UnloadContent();

	game->DestroyInstance();

return 0;
}