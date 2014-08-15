#include "CGame.h"
#define MUSIC_FADE_IN 2000

class CIntroState: public CGameState
{
public:
	void Init();
	void Finalize();

	void Pause();
	void Resume();

	void Draw(CGame *game);
	void HandleEvents(CGame *game);
	void Update(CGame *game);

	static CIntroState *GetInstance()
	{
		if(inst == 0)
		{
			inst = new CIntroState();
		}

		return inst;
	}

protected:
	CIntroState(){}


private:
	static CIntroState *inst;

	SDL_Surface *text;
	SDL_Color textColor;

	SDL_Surface *bg;

	Button *myButton;

	bool musicStarted;
};


