#include "CGame.h"
#include "CInGameState.h"

class CStartMenuState: public CGameState
{
public:
	void Init();
	void Finalize();

	void Pause();
	void Resume();

	void Draw(CGame *game);
	void HandleEvents(CGame *game);
	void Update(CGame *game);

	static CStartMenuState *GetInstance()
	{
		if(inst == 0)
		{
			inst = new CStartMenuState();
		}

		return inst;
	}

protected:
	CStartMenuState(){}


private:
	static CStartMenuState *inst;

	TTF_Font *menuFont;

	SDL_Surface *text;
	SDL_Surface *text2;
	SDL_Surface *text3;
	SDL_Surface *text4;
	SDL_Surface *text5;
	SDL_Surface *text6;
	SDL_Surface *text7;
	SDL_Surface *text8;
	SDL_Surface *text9;

	SDL_Surface *heart;

	SDL_Color textColor;

	SDL_Surface *fader;

	Button *button;

	int alpha;

	bool fadedin;

};