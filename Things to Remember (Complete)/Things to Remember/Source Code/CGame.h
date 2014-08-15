#ifndef CGAME_H
#define CGAME_H

#include "Globals.h"
#include "CObject.h"
#include "CPSysMan.h"

class CGameState;

class CGame
{
    private:

		static CGame *inst;

		 CGame();
        ~CGame();
        
		bool m_Running;

		bool m_FullScreen;

    public:

		static CGame *GetInstance();

        bool Initialize();

        bool LoadContent();

        void UnloadContent();

        void Update();

        void Draw();

		void EventHandler();

		void ChangeState(CGameState *state);

		void PushState(CGameState *state);

		void PopState();

		void DestroyInstance();

		bool isRunning()
		{
			return m_Running;
		}

		void ToggleFullScreen();

		void StopRunning()
		{
			m_Running = false;
		}

		vector<CGameState *> GameStates; //GameState stack

		Mix_Chunk *music; // for loading a song to use throughout game
						  // is public for direct manipulation

};

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Finalize() = 0;

	virtual void Pause()  = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(CGame *game) = 0;
	virtual void Draw(CGame *game)	       = 0;
	virtual void Update(CGame *game)       = 0;

	void ChangeState(CGame *game, CGameState *state)
	{
		game->ChangeState(state);
	}
};

#endif