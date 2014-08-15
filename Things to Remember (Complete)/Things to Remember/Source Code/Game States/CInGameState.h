#include "CGame.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "LevelManager.h"

#define MUSIC_FADE_OUT 1000

class CInGameState: public CGameState
{
public:
	void Init();
	void Finalize();

	void Pause();
	void Resume();

	void Draw(CGame *game);
	void HandleEvents(CGame *game);
	void Update(CGame *game);

	static CInGameState *GetInstance()
	{
		if(inst == 0)
		{
			inst = new CInGameState();
		}

		return inst;
	}

protected:
	CInGameState(){}


private:
	static CInGameState *inst;

	SDL_Surface *text;
	SDL_Color textColor;

	SDL_Surface *tileSheet;
	Player       *player;

	SDL_Rect tileClips[9];

	PSysMan *myPSysMan;

	LevelMan *levelMan;
};