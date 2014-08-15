#include "CGame.h"
#include "CIntroState.h"

CGame::CGame()
{
	m_Running    = true;
	m_FullScreen = true;
}

CGame::~CGame()
{
}

CGame *CGame::inst = 0;

CGame *CGame::GetInstance()
{
	if(inst == 0)
	{
		inst = new CGame();
	}

	return inst;
}

bool CGame::Initialize()
{
	Debug *dbg = Debug::GetInstance();

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		dbg->Print("SDL_Init Failed /n");
		return false;
	}

	if(m_FullScreen == true)
	{

		mainScreen = SDL_SetVideoMode(SCREEN_W,SCREEN_H,SCREEN_BPP,SDL_SWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
	}
	else if(m_FullScreen == false)
	{
		mainScreen = SDL_SetVideoMode(SCREEN_W,SCREEN_H,SCREEN_BPP,SDL_SWSURFACE);
	}


	if(mainScreen == NULL)
	{
		dbg->Print("Could not Initialize Screen!");
		return false;
	}

	if(TTF_Init() == -1)
	{
		dbg->Print("TTF_Init Failed");
		return false;
	}
	
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096) == -1)
	{
		dbg->Print("SDL_Mixer failed/n");
		return false;
	}

	SDL_WM_SetCaption("Alana's Valentine's Day Gift", NULL);
	
	return true;
}

bool CGame::LoadContent()
{
	font = TTF_OpenFont("dnealiancursive.ttf", 36);
	
	if(font == NULL)
	{
		return false;
	}


	//-- Load game content here

	music = Mix_LoadWAV("Sweet Music.wav"); // Load Music
	ChangeState(CIntroState::GetInstance());

	//--

	return true;
}

void CGame::UnloadContent()
{
	
	// Release game content, Free Surfaces, Close Libraries
	if(!GameStates.empty())
	{
		GameStates.back()->Finalize();
		GameStates.pop_back();
	}

	Mix_FreeChunk(music);

	/************************************************/
	TTF_CloseFont(font);
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}
void CGame::ChangeState(CGameState *state)
{
	if(!GameStates.empty()) // if there is a state, clean it up and pop it off
	{
		GameStates.back()->Finalize();
		GameStates.pop_back();
	}

	GameStates.push_back(state); // push on the new one and initialize it
	GameStates.back()->Init();
}

void CGame::PushState(CGameState *state)
{
	if(!GameStates.empty())  // pause state if there is one already on stack
	{
		GameStates.back()->Pause();
	}

	GameStates.push_back(state); // push state onto stack and initialize it
	GameStates.back()->Init();
}

void CGame::PopState()
{
	if(!GameStates.empty())//if somethings on the stack and finish up state then pop it off
	{
		GameStates.back()->Finalize();
		GameStates.pop_back();
	}

	if(!GameStates.empty()) // if there's a state left, it is paused, so resume it
	{
		GameStates.back()->Resume();
	}
}

void CGame::Update()
{
	// Place Update logic here
	GameStates.back()->Update(this);

}

void CGame::Draw()
{
	// Place Rendering logic here
	GameStates.back()->Draw(this);	
	
} 

void CGame::EventHandler()
{
	//Place Event Handling Functions here
	GameStates.back()->HandleEvents(this);
}

void CGame::DestroyInstance()
{
	delete inst;

	inst = 0;
}

void CGame::ToggleFullScreen()
{
	if(m_FullScreen == false)
	{
		mainScreen = SDL_SetVideoMode(SCREEN_W,SCREEN_H,SCREEN_BPP,SDL_SWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
		m_FullScreen = true;
	}
	else if(m_FullScreen == true)
	{
		mainScreen = SDL_SetVideoMode(SCREEN_W,SCREEN_H,SCREEN_BPP,SDL_SWSURFACE);
		m_FullScreen = false;
	}
}