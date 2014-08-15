#include "CGame.h"

class CMenuState: public CGameState
{
public:
	void Init();
	void Finalize();

	void Pause();
	void Resume();

	void Draw(CGame *game);
	void HandleEvents(CGame *game);
	void Update(CGame *game);

	static CMenuState *GetInstance()
	{
		if(inst == 0)
		{
			inst = new CMenuState();
		}

		return inst;
	}

protected:
	CMenuState(){}


private:
	static CMenuState *inst;

	SDL_Surface *text;
	SDL_Color textColor;

};