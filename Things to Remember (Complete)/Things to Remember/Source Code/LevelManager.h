#ifndef _CLEVELMAN_H
#define _CLEVELMAN_H

#include "CLevel.h"
#include "CPlayer.h"
#include "CPSysMan.h"


class LevelMan
{
public:
	LevelMan(string initMap);
	~LevelMan();

	void StartNextLevel();

	int levelCount;

	void Update(Player *Player, PSysMan *PSysMan);
	void Draw(SDL_Rect *TileClips,SDL_Surface *tileSheet, Player *player, PSysMan *myPSysMan);
	void Handle_Events(SDL_Event event);

	void Finalize();

	Level *GetLevel()
	{
		return curLevel;
	}

	bool isLevelFinished()
	{
		return levelFinished;
	}

	void FinishLevel()
	{
		levelFinished = true;
	}

private:
	Level *curLevel;
	
	bool levelFinished;

};

#endif